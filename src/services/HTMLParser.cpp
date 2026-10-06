#include "HTMLParser.h"
#include <cctype>

namespace Rebellion
{

	bool IsBlockTag(const std::string &tag)
	{
		return tag == "p" || tag == "div" || tag == "br" || tag == "li" ||
			   tag == "h1" || tag == "h2" || tag == "h3" || tag == "h4" ||
			   tag == "h5" || tag == "h6" || tag == "tr" || tag == "section" ||
			   tag == "article";
	}

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
		if (!entity.empty() && entity[0] == '#')
		{
			try
			{
				const bool hex = entity.size() > 2 && (entity[1] == 'x' || entity[1] == 'X');
				const auto codepoint = std::stoul(entity.substr(hex ? 2 : 1), nullptr, hex ? 16 : 10);
				if (codepoint >= 32 && codepoint <= 126)
				{
					return std::string(1, static_cast<char>(codepoint));
				}
				if (codepoint == 9 || codepoint == 10 || codepoint == 13 || codepoint == 160)
				{
					return " ";
				}
			}
			catch (const std::exception &)
			{
			}
		}
		return "&" + entity + ";";
	}

	std::string HtmlToText(const std::string &html)
	{
		std::string text;
		bool inTag = false;
		bool pendingSpace = false;
		bool pendingNewline = false;
		std::string tag;
		std::string hiddenTag;

		for (size_t i = 0; i < html.size(); ++i)
		{
			const char ch = html[i];
			if (inTag)
			{
				if (ch == '>')
				{
					inTag = false;
					std::string normalizedTag;
					const size_t tagStart = !tag.empty() && tag[0] == '/' ? 1 : 0;
					for (size_t tagIndex = tagStart; tagIndex < tag.size(); ++tagIndex)
					{
						const char c = tag[tagIndex];
						if (std::isspace(static_cast<unsigned char>(c)) || c == '/')
							break;
						normalizedTag += static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
					}
					const bool closing = !tag.empty() && tag[0] == '/';
					if (normalizedTag == "script" || normalizedTag == "style")
					{
						if (closing)
							hiddenTag.clear();
						else
							hiddenTag = normalizedTag;
					}
					if (hiddenTag.empty() && IsBlockTag(normalizedTag))
						pendingNewline = true;
					tag.clear();
				}
				else
				{
					tag += ch;
				}
				continue;
			}

			if (!hiddenTag.empty())
			{
				if (ch == '<')
				{
					inTag = true;
					tag.clear();
				}
				continue;
			}
			if (ch == '<')
			{
				inTag = true;
				tag.clear();
				continue;
			}
			if (ch == '&')
			{
				const auto end = html.find(';', i + 1);
				if (end != std::string::npos && end - i <= 12)
				{
					const std::string decoded = DecodeEntity(html.substr(i + 1, end - i - 1));
					if (decoded == " ")
						pendingSpace = true;
					else
					{
						if (pendingNewline && !text.empty() && text.back() != '\n')
							text += '\n';
						else if (pendingSpace && !text.empty() && !std::isspace(static_cast<unsigned char>(text.back())))
							text += ' ';
						text += decoded;
					}
					pendingSpace = false;
					pendingNewline = false;
					i = end;
					continue;
				}
			}
			if (std::isspace(static_cast<unsigned char>(ch)))
			{
				if (ch == '\n' || ch == '\r')
					pendingNewline = true;
				else
					pendingSpace = true;
				continue;
			}
			if (pendingNewline && !text.empty() && text.back() != '\n')
				text += '\n';
			else if (pendingSpace && !text.empty() && text.back() != '\n' && !std::isspace(static_cast<unsigned char>(text.back())))
				text += ' ';
			text += ch;
			pendingSpace = false;
			pendingNewline = false;
		}

		while (!text.empty() && std::isspace(static_cast<unsigned char>(text.back())))
			text.pop_back();
		return text;
	}

} // namespace Rebellion
