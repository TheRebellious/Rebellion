#include "HTMLParser.h"

#include <cctype>
#include <exception>

namespace
{
	// Parser implementation details stay private to this translation unit.

	/** Return a lowercase tag name without its closing slash or attributes. */
	std::string NormalizeTagName(const std::string &tag)
	{
		const size_t nameStart = !tag.empty() && tag.front() == '/' ? 1 : 0;
		std::string name;

		for (size_t i = nameStart; i < tag.size(); ++i)
		{
			const unsigned char character = static_cast<unsigned char>(tag[i]);
			if (std::isspace(character) || character == '/')
				break;

			name += static_cast<char>(std::tolower(character));
		}

		return name;
	}

	/** Return whether the tag's contents should be omitted from output. */
	bool IsHiddenTag(const std::string &tag)
	{
		// Script and style contents are source code or presentation rules, not text.
		return tag == "script" || tag == "style";
	}

	/** Find an attribute value in a raw tag, supporting quoted and bare values. */
	std::string ExtractAttribute(const std::string &tag, const std::string &attribute)
	{
		size_t position = 0;
		while (position < tag.size() && !std::isspace(static_cast<unsigned char>(tag[position])))
			++position;

		while (position < tag.size())
		{
			// Skip separators before reading each attribute name.
			while (position < tag.size() &&
				   (std::isspace(static_cast<unsigned char>(tag[position])) || tag[position] == '/'))
				++position;

			const size_t nameStart = position;
			while (position < tag.size() && tag[position] != '=' && tag[position] != '/' &&
				   !std::isspace(static_cast<unsigned char>(tag[position])))
				++position;
			if (nameStart == position)
				break;

			std::string name = tag.substr(nameStart, position - nameStart);
			for (char &character : name)
				character = static_cast<char>(std::tolower(static_cast<unsigned char>(character)));

			while (position < tag.size() && std::isspace(static_cast<unsigned char>(tag[position])))
				++position;
			if (position == tag.size() || tag[position] != '=')
				continue;

			++position;
			while (position < tag.size() && std::isspace(static_cast<unsigned char>(tag[position])))
				++position;

			std::string value;
			if (position < tag.size() && (tag[position] == '\'' || tag[position] == '"'))
			{
				// A quoted value may contain whitespace and slashes.
				const char quote = tag[position++];
				const size_t valueStart = position;
				while (position < tag.size() && tag[position] != quote)
					++position;
				value = tag.substr(valueStart, position - valueStart);
				if (position < tag.size())
					++position;
			}
			else
			{
				// Bare attribute values end at whitespace or a self-closing slash.
				const size_t valueStart = position;
				while (position < tag.size() && !std::isspace(static_cast<unsigned char>(tag[position])) &&
					   tag[position] != '/')
					++position;
				value = tag.substr(valueStart, position - valueStart);
			}

			if (name == attribute)
				return value;
		}

		return {};
	}

	/** Add one deferred source-space or line break before the next text. */
	void AppendPendingWhitespace(std::string &text, bool pendingSpace, bool pendingNewline)
	{
		if (pendingNewline && !text.empty() && text.back() != '\n')
		{
			text += '\n';
		}
		else if (pendingSpace && !text.empty() && text.back() != '\n' &&
				 !std::isspace(static_cast<unsigned char>(text.back())))
		{
			text += ' ';
		}
	}

	/** Apply side effects from a completed tag, including links and hidden text. */
	void HandleTag(const std::string &tag, std::string &hiddenTag, bool &pendingNewline,
				std::string &text, bool &pendingSpace, bool &inLink)
	{
		const std::string name = NormalizeTagName(tag);
		const bool closing = !tag.empty() && tag.front() == '/';

		if (name == "a")
		{
			if (closing)
			{
				// Separate the redirect label from any text that follows the anchor.
				inLink = false;
				pendingSpace = true;
			}
			else
			{
				const std::string href = ExtractAttribute(tag, "href");
				if (!href.empty())
				{
					// Show the destination in place of the anchor's display text.
					AppendPendingWhitespace(text, pendingSpace, pendingNewline);
					text += "Redirect: " + href;
					pendingSpace = true;
					pendingNewline = false;
					inLink = true;
				}
			}
		}

		if (IsHiddenTag(name))
			hiddenTag = closing ? std::string{} : name;

		if (hiddenTag.empty() && IsBlockTag(name))
			pendingNewline = true;
	}

	/** Decode an entity at index and advance index through its semicolon. */
	bool TryAppendEntity(const std::string &html, size_t &index, std::string &text,
						 bool &pendingSpace, bool &pendingNewline)
	{
		const size_t entityEnd = html.find(';', index + 1);
		if (entityEnd == std::string::npos || entityEnd - index > 12)
			return false;

		const std::string entity = html.substr(index + 1, entityEnd - index - 1);
		const std::string decoded = DecodeEntity(entity);
		if (decoded == " ")
		{
			pendingSpace = true;
		}
		else
		{
			AppendPendingWhitespace(text, pendingSpace, pendingNewline);
			text += decoded;
		}

		pendingSpace = false;
		pendingNewline = false;
		index = entityEnd;
		return true;
	}

	/** Append a visible character after emitting any deferred whitespace. */
	void AppendCharacter(char character, std::string &text, bool &pendingSpace,
					 bool &pendingNewline)
	{
		AppendPendingWhitespace(text, pendingSpace, pendingNewline);
		text += character;
		pendingSpace = false;
		pendingNewline = false;
	}
} // namespace

/** Return whether the normalized tag is one of the parser's line-break tags. */
bool IsBlockTag(const std::string &tag)
{
	return tag == "p" || tag == "div" || tag == "br" || tag == "li" ||
		   tag == "h1" || tag == "h2" || tag == "h3" || tag == "h4" ||
		   tag == "h5" || tag == "h6" || tag == "tr" || tag == "section" ||
		   tag == "article";
}

/** Decode the named entities supported here and basic numeric ASCII entities. */
std::string DecodeEntity(const std::string &entity)
{
	if (entity == "amp")
		return "&";
	if (entity == "lt")
		return "<";
	if (entity == "gt")
		return ">";
	if (entity == "quot")
		return "\"";
	if (entity == "apos" || entity == "#39")
		return "'";
	if (entity == "nbsp")
		return " ";

	if (!entity.empty() && entity.front() == '#')
	{
		try
		{
			const bool hexadecimal = entity.size() > 2 &&
				(entity[1] == 'x' || entity[1] == 'X');
			const auto codepoint = std::stoul(entity.substr(hexadecimal ? 2 : 1), nullptr,
										   hexadecimal ? 16 : 10);

			if (codepoint >= 32 && codepoint <= 126)
				return std::string(1, static_cast<char>(codepoint));
			if (codepoint == 9 || codepoint == 10 || codepoint == 13 || codepoint == 160)
				return " ";
		}
		catch (const std::exception &)
		{
			// Invalid numeric syntax is preserved by the fallback below.
		}
	}

	return "&" + entity + ";";
}

/** Strip markup while preserving readable spacing and link destinations. */
std::string HtmlToText(const std::string &html)
{
	std::string text;
	std::string tag;
	std::string hiddenTag;
	bool inTag = false;
	bool pendingSpace = false;
	bool pendingNewline = false;
	bool inLink = false;

	// Deferred whitespace is emitted only when visible text follows it.
	for (size_t i = 0; i < html.size(); ++i)
	{
		const char character = html[i];

		if (inTag)
		{
			if (character == '>')
			{
				inTag = false;
				HandleTag(tag, hiddenTag, pendingNewline, text, pendingSpace, inLink);
				tag.clear();
			}
			else
			{
				tag += character;
			}
			continue;
		}

		if (!hiddenTag.empty())
		{
			if (character == '<')
			{
				inTag = true;
				tag.clear();
			}
			continue;
		}

		if (inLink)
			// The href has already been written; discard the anchor label.
			continue;

		if (character == '<')
		{
			inTag = true;
			tag.clear();
			continue;
		}

		if (character == '&' && TryAppendEntity(html, i, text, pendingSpace, pendingNewline))
			continue;

		if (std::isspace(static_cast<unsigned char>(character)))
		{
			if (character == '\n' || character == '\r')
				pendingNewline = true;
			else
				pendingSpace = true;
			continue;
		}

		AppendCharacter(character, text, pendingSpace, pendingNewline);
	}

	while (!text.empty() && std::isspace(static_cast<unsigned char>(text.back())))
		text.pop_back();

	return text;
}
