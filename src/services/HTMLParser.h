#pragma once

#include <string>

/**
 * @brief Check whether an HTML tag should introduce a line break.
 * @param tag Lowercase tag name without angle brackets or attributes.
 * @return `true` when the tag is treated as a block element.
 */
bool IsBlockTag(const std::string &tag);

/**
 * @brief Decode a supported named or numeric HTML entity.
 * @param entity Entity contents without the surrounding `&` and `;`.
 * @return The decoded character, or the original entity spelling if unsupported.
 */
std::string DecodeEntity(const std::string &entity);

/**
 * @brief Convert HTML markup to readable plain text.
 *
 * Tags are removed, supported entities are decoded, script and style contents
 * are omitted, and block tags and source whitespace are represented as text
 * spacing. Anchors with an `href` are rendered as `Redirect: <href>`.
 * @param html HTML source to convert.
 * @return Plain-text representation of the source.
 */
std::string HtmlToText(const std::string &html);
