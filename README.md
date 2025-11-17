The parser class is designed to extract and clean key-value information from tables in ASCII format. It processes raw text in table form, removes formatting characters, combines parameter names with their numerical values if necessary, and provides easy access to parsed rows or individual parameters. This parser is useful when working with tables that use |, -, +, and spaces for formatting, but the actual data must be extracted as plain text pairs (e.g., “Bandwidth 20”).

Here's an example of a table I parsed in table.txt.

Translated with DeepL.com (free version)
