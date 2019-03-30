/* Generated by re2c 1.1.1 on Sat Mar 30 02:03:47 2019 */
#pragma once

#include <ciso646>
#include <iostream>

namespace simo
{

namespace shapes
{

/*!
 * @brief a Well-known text (WKT) markup language lexer
 *
 * @since 0.0.1
 */
class WktLexer
{
  public:

    /*!
     * @brief creates a wkt lexer from the given source
     * @param source the source string
     *
     * @since 0.0.1
     */
    WktLexer(const char* source)
        : content(source)
    {
        start = cursor = source;
        limit          = content + strlen(source);
    }

    /*!
     * @brief scan the next token
     * @return the numeric token identifier
     *
     * @since 0.0.1
     */
    int scan()
    {

        /// pointer for backtracking information
        const char* marker = nullptr;

        start = cursor;

        
{
	char yych;
	unsigned int yyaccept = 0;
	static const unsigned char yybm[] = {
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0, 128, 128,   0,   0, 128,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		128,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		 64,  64,  64,  64,  64,  64,  64,  64, 
		 64,  64,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
	};
	yych = *cursor;
	if (yych <= '+') {
		if (yych <= '\r') {
			if (yych <= 0x08) {
				if (yych >= 0x01) goto shapes_wkt_lexer_4;
			} else {
				if (yych <= '\n') goto shapes_wkt_lexer_6;
				if (yych <= '\f') goto shapes_wkt_lexer_4;
				goto shapes_wkt_lexer_6;
			}
		} else {
			if (yych <= '\'') {
				if (yych == ' ') goto shapes_wkt_lexer_6;
				goto shapes_wkt_lexer_4;
			} else {
				if (yych <= '(') goto shapes_wkt_lexer_8;
				if (yych <= ')') goto shapes_wkt_lexer_10;
				goto shapes_wkt_lexer_4;
			}
		}
	} else {
		if (yych <= 'D') {
			if (yych <= '/') {
				if (yych <= ',') goto shapes_wkt_lexer_12;
				if (yych <= '-') goto shapes_wkt_lexer_14;
				goto shapes_wkt_lexer_4;
			} else {
				if (yych <= '0') goto shapes_wkt_lexer_15;
				if (yych <= '9') goto shapes_wkt_lexer_17;
				goto shapes_wkt_lexer_4;
			}
		} else {
			if (yych <= 'M') {
				if (yych <= 'E') goto shapes_wkt_lexer_19;
				if (yych <= 'L') goto shapes_wkt_lexer_4;
				goto shapes_wkt_lexer_20;
			} else {
				if (yych == 'P') goto shapes_wkt_lexer_21;
				goto shapes_wkt_lexer_4;
			}
		}
	}
	++cursor;
	{ return WKT_END_OF_INPUT; }
shapes_wkt_lexer_4:
	++cursor;
shapes_wkt_lexer_5:
	{ return WKT_PARSE_ERROR; }
shapes_wkt_lexer_6:
	++cursor;
	{ return scan(); }
shapes_wkt_lexer_8:
	++cursor;
	{ return WKT_LPAREN; }
shapes_wkt_lexer_10:
	++cursor;
	{ return WKT_RPAREN; }
shapes_wkt_lexer_12:
	++cursor;
	{ return WKT_COMMA; }
shapes_wkt_lexer_14:
	yych = *++cursor;
	if (yych <= '/') goto shapes_wkt_lexer_5;
	if (yych <= '0') goto shapes_wkt_lexer_15;
	if (yych <= '9') goto shapes_wkt_lexer_17;
	goto shapes_wkt_lexer_5;
shapes_wkt_lexer_15:
	yyaccept = 0;
	yych = *(marker = ++cursor);
	if (yych <= 'D') {
		if (yych == '.') goto shapes_wkt_lexer_22;
	} else {
		if (yych <= 'E') goto shapes_wkt_lexer_24;
		if (yych == 'e') goto shapes_wkt_lexer_24;
	}
shapes_wkt_lexer_16:
	{ return WKT_NUM; }
shapes_wkt_lexer_17:
	yyaccept = 0;
	yych = *(marker = ++cursor);
	if (yybm[0+yych] & 64) {
		goto shapes_wkt_lexer_17;
	}
	if (yych <= 'D') {
		if (yych == '.') goto shapes_wkt_lexer_22;
		goto shapes_wkt_lexer_16;
	} else {
		if (yych <= 'E') goto shapes_wkt_lexer_24;
		if (yych == 'e') goto shapes_wkt_lexer_24;
		goto shapes_wkt_lexer_16;
	}
shapes_wkt_lexer_19:
	yyaccept = 1;
	yych = *(marker = ++cursor);
	if (yych == 'M') goto shapes_wkt_lexer_25;
	goto shapes_wkt_lexer_5;
shapes_wkt_lexer_20:
	yyaccept = 1;
	yych = *(marker = ++cursor);
	if (yych == 'U') goto shapes_wkt_lexer_26;
	goto shapes_wkt_lexer_5;
shapes_wkt_lexer_21:
	yyaccept = 1;
	yych = *(marker = ++cursor);
	if (yych == 'O') goto shapes_wkt_lexer_27;
	goto shapes_wkt_lexer_5;
shapes_wkt_lexer_22:
	yych = *++cursor;
	if (yych <= '/') goto shapes_wkt_lexer_23;
	if (yych <= '9') goto shapes_wkt_lexer_28;
shapes_wkt_lexer_23:
	cursor = marker;
	if (yyaccept <= 1) {
		if (yyaccept == 0) {
			goto shapes_wkt_lexer_16;
		} else {
			goto shapes_wkt_lexer_5;
		}
	} else {
		if (yyaccept == 2) {
			goto shapes_wkt_lexer_43;
		} else {
			goto shapes_wkt_lexer_57;
		}
	}
shapes_wkt_lexer_24:
	yych = *++cursor;
	if (yych <= ',') {
		if (yych == '+') goto shapes_wkt_lexer_30;
		goto shapes_wkt_lexer_23;
	} else {
		if (yych <= '-') goto shapes_wkt_lexer_30;
		if (yych <= '/') goto shapes_wkt_lexer_23;
		if (yych <= '9') goto shapes_wkt_lexer_31;
		goto shapes_wkt_lexer_23;
	}
shapes_wkt_lexer_25:
	yych = *++cursor;
	if (yych == 'P') goto shapes_wkt_lexer_33;
	goto shapes_wkt_lexer_23;
shapes_wkt_lexer_26:
	yych = *++cursor;
	if (yych == 'L') goto shapes_wkt_lexer_34;
	goto shapes_wkt_lexer_23;
shapes_wkt_lexer_27:
	yych = *++cursor;
	if (yych == 'I') goto shapes_wkt_lexer_35;
	goto shapes_wkt_lexer_23;
shapes_wkt_lexer_28:
	yyaccept = 0;
	yych = *(marker = ++cursor);
	if (yych <= 'D') {
		if (yych <= '/') goto shapes_wkt_lexer_16;
		if (yych <= '9') goto shapes_wkt_lexer_28;
		goto shapes_wkt_lexer_16;
	} else {
		if (yych <= 'E') goto shapes_wkt_lexer_24;
		if (yych == 'e') goto shapes_wkt_lexer_24;
		goto shapes_wkt_lexer_16;
	}
shapes_wkt_lexer_30:
	yych = *++cursor;
	if (yych <= '/') goto shapes_wkt_lexer_23;
	if (yych >= ':') goto shapes_wkt_lexer_23;
shapes_wkt_lexer_31:
	yych = *++cursor;
	if (yych <= '/') goto shapes_wkt_lexer_16;
	if (yych <= '9') goto shapes_wkt_lexer_31;
	goto shapes_wkt_lexer_16;
shapes_wkt_lexer_33:
	yych = *++cursor;
	if (yych == 'T') goto shapes_wkt_lexer_36;
	goto shapes_wkt_lexer_23;
shapes_wkt_lexer_34:
	yych = *++cursor;
	if (yych == 'T') goto shapes_wkt_lexer_37;
	goto shapes_wkt_lexer_23;
shapes_wkt_lexer_35:
	yych = *++cursor;
	if (yych == 'N') goto shapes_wkt_lexer_38;
	goto shapes_wkt_lexer_23;
shapes_wkt_lexer_36:
	yych = *++cursor;
	if (yych == 'Y') goto shapes_wkt_lexer_39;
	goto shapes_wkt_lexer_23;
shapes_wkt_lexer_37:
	yych = *++cursor;
	if (yych == 'I') goto shapes_wkt_lexer_41;
	goto shapes_wkt_lexer_23;
shapes_wkt_lexer_38:
	yych = *++cursor;
	if (yych == 'T') goto shapes_wkt_lexer_42;
	goto shapes_wkt_lexer_23;
shapes_wkt_lexer_39:
	++cursor;
	{ return WKT_EMPTY_SET; }
shapes_wkt_lexer_41:
	yych = *++cursor;
	if (yych == 'P') goto shapes_wkt_lexer_44;
	goto shapes_wkt_lexer_23;
shapes_wkt_lexer_42:
	yyaccept = 2;
	yych = *(marker = ++cursor);
	if (yybm[0+yych] & 128) {
		goto shapes_wkt_lexer_45;
	}
	if (yych == 'M') goto shapes_wkt_lexer_47;
	if (yych == 'Z') goto shapes_wkt_lexer_49;
shapes_wkt_lexer_43:
	{ return WKT_POINT_TAGGED_TEXT; }
shapes_wkt_lexer_44:
	yych = *++cursor;
	if (yych == 'O') goto shapes_wkt_lexer_51;
	goto shapes_wkt_lexer_23;
shapes_wkt_lexer_45:
	yych = *++cursor;
	if (yybm[0+yych] & 128) {
		goto shapes_wkt_lexer_45;
	}
	if (yych == 'M') goto shapes_wkt_lexer_47;
	if (yych == 'Z') goto shapes_wkt_lexer_49;
	goto shapes_wkt_lexer_23;
shapes_wkt_lexer_47:
	++cursor;
	{ return WKT_POINT_M_TAGGED_TEXT; }
shapes_wkt_lexer_49:
	yych = *++cursor;
	if (yych == 'M') goto shapes_wkt_lexer_52;
	{ return WKT_POINT_Z_TAGGED_TEXT; }
shapes_wkt_lexer_51:
	yych = *++cursor;
	if (yych == 'I') goto shapes_wkt_lexer_54;
	goto shapes_wkt_lexer_23;
shapes_wkt_lexer_52:
	++cursor;
	{ return WKT_POINT_ZM_TAGGED_TEXT; }
shapes_wkt_lexer_54:
	yych = *++cursor;
	if (yych != 'N') goto shapes_wkt_lexer_23;
	yych = *++cursor;
	if (yych != 'T') goto shapes_wkt_lexer_23;
	yyaccept = 3;
	yych = *(marker = ++cursor);
	if (yych <= 0x1F) {
		if (yych <= '\n') {
			if (yych >= '\t') goto shapes_wkt_lexer_58;
		} else {
			if (yych == '\r') goto shapes_wkt_lexer_58;
		}
	} else {
		if (yych <= 'M') {
			if (yych <= ' ') goto shapes_wkt_lexer_58;
			if (yych >= 'M') goto shapes_wkt_lexer_60;
		} else {
			if (yych == 'Z') goto shapes_wkt_lexer_62;
		}
	}
shapes_wkt_lexer_57:
	{ return WKT_MULTIPOINT_TAGGED_TEXT; }
shapes_wkt_lexer_58:
	yych = *++cursor;
	if (yych <= 0x1F) {
		if (yych <= '\n') {
			if (yych <= 0x08) goto shapes_wkt_lexer_23;
			goto shapes_wkt_lexer_58;
		} else {
			if (yych == '\r') goto shapes_wkt_lexer_58;
			goto shapes_wkt_lexer_23;
		}
	} else {
		if (yych <= 'M') {
			if (yych <= ' ') goto shapes_wkt_lexer_58;
			if (yych <= 'L') goto shapes_wkt_lexer_23;
		} else {
			if (yych == 'Z') goto shapes_wkt_lexer_62;
			goto shapes_wkt_lexer_23;
		}
	}
shapes_wkt_lexer_60:
	++cursor;
	{ return WKT_MULTIPOINT_M_TAGGED_TEXT; }
shapes_wkt_lexer_62:
	yych = *++cursor;
	if (yych == 'M') goto shapes_wkt_lexer_64;
	{ return WKT_MULTIPOINT_Z_TAGGED_TEXT; }
shapes_wkt_lexer_64:
	++cursor;
	{ return WKT_MULTIPOINT_ZM_TAGGED_TEXT; }
}

    }

    /*!
     * @brief returns the current token string
     * @return the token string
     *
     * @since 0.0.1
     */
    std::string get_token() const
    {
        return std::string(reinterpret_cast<const char*>(start), static_cast<size_t>(cursor - start));
    }

  private:
    /// pointer to the buffer
    const char* content = nullptr;

    /// pointer to the beginning of the current token
    const char* start = nullptr;

    /// pointer to the current token
    const char* cursor = nullptr;

    /// pointer to the end of the buffer
    const char* limit = nullptr;
};

}  // namespace shapes
}  // namespace simo