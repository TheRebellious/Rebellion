#pragma once

#include <string>

// Checks if a tag is a block-level element that should create line breaks
bool IsBlockTag(const std::string &tag);

// Decodes HTML entities to their character equivalents
std::string DecodeEntity(const std::string &entity);

// Converts HTML content to plain text by stripping tags and decoding entities
std::string HtmlToText(const std::string &html);
