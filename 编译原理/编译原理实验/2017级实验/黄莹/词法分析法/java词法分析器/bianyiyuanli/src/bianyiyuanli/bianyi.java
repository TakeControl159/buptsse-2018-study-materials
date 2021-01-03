package bianyiyuanli;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.HashMap;
import java.util.Map;

class Binary {
	int category = 0;
	int index = 0;
	String value = "-";

	public Binary(int c, int i, String v) {
		category = c;
		index = i;
		value = v;
	}
}

public class bianyi {
	String inputStr;// 输入符号串
	int index;// 输入符号读入字符的位置
	int line = 1;// 行数
	int id_word_num = 0;// id个数
	int ch_num = 0;// 字符个数
	int num_word_num = 0;// 数字个数
	int keyword_num = 0;// 关键字个数
	int bound_word_num = 0;// 边界符号个数
	int operater_word_num = 0;// 操作数个数
	char character;// 最新读入的字符
	String token;// 已读入的字符
	Map<String, Integer> id = new HashMap<String, Integer>();// 标识符集
	int len = 100;
	String keyWord[] = new String[len];// 保留字表
	String Boundary[] = new String[2 * len];// 界符
	String Operator[] = new String[3 * len];// 运算符

	void keyWord_init() {
		keyWord[0] = "auto";
		keyWord[1] = "double";
		keyWord[2] = "int";
		keyWord[3] = "struct";
		keyWord[4] = "break";
		keyWord[5] = "else";
		keyWord[6] = "long";
		keyWord[7] = "switch";
		keyWord[8] = "case";
		keyWord[9] = "enum";
		keyWord[10] = "register";
		keyWord[11] = "typedef";
		keyWord[12] = "char";
		keyWord[13] = "extern";
		keyWord[14] = "return";
		keyWord[15] = "union";
		keyWord[16] = "const";
		keyWord[17] = "float";
		keyWord[18] = "short";
		keyWord[19] = "unsigned";
		keyWord[20] = "continue";
		keyWord[21] = "for";
		keyWord[22] = "signed";
		keyWord[23] = "void";
		keyWord[24] = "default";
		keyWord[25] = "goto";
		keyWord[26] = "sizeof";
		keyWord[27] = "volatile";
		keyWord[28] = "do";
		keyWord[29] = "if";
		keyWord[30] = "while";
		keyWord[31] = "static";
		keyWord[32] = "main";
		keyWord[33] = "read";
		keyWord[34] = "write";
		keyWord[35] = "bool";
		keyWord[36] = "catch";
		keyWord[37] = "class";
		keyWord[38] = "delete";
		keyWord[39] = "false";
		keyWord[40] = "true";
		keyWord[41] = "friend";
		keyWord[42] = "inline";
		keyWord[43] = "new";
		keyWord[44] = "private";
		keyWord[45] = "protected";
		keyWord[46] = "public";
		keyWord[47] = "this";
		keyWord[48] = "try";
		keyWord[49] = "using";
		keyWord[50] = "virtual";
		keyWord[51] = "include";
		keyWord[52] = "namespace";
		keyWord[53] = "std";
		keyWord[54] = "iostream";
	}

	void bound_init() {
		Boundary[121] = "{";
		Boundary[122] = "}";
		Boundary[123] = "[";
		Boundary[124] = "]";
		Boundary[125] = ";";
		Boundary[126] = ",";
		Boundary[127] = ".";
		Boundary[128] = "(";
		Boundary[129] = ")";
		Boundary[130] = ":";
		Boundary[131] = "/*";
		Boundary[132] = "#";
		Boundary[133] = "*/";
		Boundary[134] = "//";
		Boundary[135] = "\"";
		Boundary[136] = "'";
	}

	void Operator_init() {
		Operator[210] = "+";
		Operator[211] = "-";
		Operator[212] = "*";
		Operator[213] = "/";
		Operator[214] = "%";
		Operator[215] = ">";
		Operator[216] = "<";
		Operator[217] = ">=";
		Operator[218] = "<=";
		Operator[219] = "==";
		Operator[220] = "-=";
		Operator[221] = "+=";
		Operator[222] = "*=";
		Operator[223] = "/=";
		Operator[224] = "!=";
		Operator[225] = "=";
		Operator[226] = "%=";
		Operator[227] = "&";
		Operator[228] = "&&";
		Operator[229] = "|";
		Operator[230] = "||";
		Operator[231] = "!";
		Operator[232] = "++";
		Operator[233] = "--";
		Operator[234] = "~";
		Operator[235] = "<<";
		Operator[236] = ">>";
		Operator[237] = "?";
	}

	void getChar() {// 读取单个字符
		character = inputStr.charAt(index++);
	}

	void get_not_blank_char() {// 读入非空白字符串
		while (character == ' ' || character == '\t') {
			getChar();
		}
	}

	void concat() {// 连接字符串
		token = token + character;
	}

	boolean is_letter() {// 判断是否字母
		if ((character >= 'A' && character <= 'Z') || (character >= 'a' && character <= 'z'))
			return true;
		return false;
	}

	boolean is_digit() {// 判断是否数字
		if (character >= '0' && character <= '9')
			return true;
		return false;
	}

	void retract() {// 回退
		character = ' ';
		index--;
	}

	int keyword_map() {// 匹配保留字符
		for (int i = 0; i < 55; i++)
			if (keyWord[i].equals(token))
				return i;
		return -1;
	}

	int id_map() {
		Integer integer = id.get(token);
		if (integer != null)
			return integer.intValue();
		else {
			id.put(token, id.size() + 1);
			return id.get(token);
		}
	}

	Binary integer_after_E_map() {
		concat();
		ch_num++;
		getChar();
		if (character == '+' || character == '-') {
			concat();
			ch_num++;
			getChar();
		}

		if (continue_int_map()) {
			return new Binary(-2, -1, token);
		} else {
			return error();
		}

	}

	boolean continue_int_map() {
		if (is_digit()) {
			concat();
			ch_num++;
			getChar();
			while (is_digit()) {
				concat();
				ch_num++;
				getChar();
			}
			retract();
			return true;
		} else {
			retract();
			return false;
		}
	}

	void jump(char s) {
		while (true) {
			if (character == s) {
				if (s == '\n')
					line++;
				else
					ch_num++;
				return;
			} else if (character == '\n')
				line++;
			else {
				ch_num++;
			}
			getChar();
		}
	}

	Binary error() {
		System.out.println("位于行" + line + "\t" + token + "\t-->\t出现错误");
		return new Binary(-3, line, "-");
	}

	Binary Analyzer() {// 词法分析程序
		token = "";
		getChar();
		get_not_blank_char();
		String val;
		int num = -1;
		switch (character) {
		case 'a':
		case 'b':
		case 'c':
		case 'd':
		case 'e':
		case 'f':
		case 'g':
		case 'h':
		case 'i':
		case 'j':
		case 'k':
		case 'l':
		case 'm':
		case 'n':
		case 'o':
		case 'p':
		case 'q':
		case 'r':
		case 's':
		case 't':
		case 'u':
		case 'v':
		case 'w':
		case 'x':
		case 'y':
		case 'z':
		case 'A':
		case 'B':
		case 'C':
		case 'D':
		case 'E':
		case 'F':
		case 'G':
		case 'H':
		case 'I':
		case 'J':
		case 'K':
		case 'L':
		case 'M':
		case 'N':
		case 'O':
		case 'P':
		case 'Q':
		case 'R':
		case 'S':
		case 'T':
		case 'U':
		case 'V':
		case 'W':
		case 'X':
		case 'Y':
		case 'Z':
			while (is_letter() || is_digit()) {// 为字母或数字
				concat();
				ch_num++;
				getChar();
			}
			retract();
			num = keyword_map();
			if (num != -1) {
				return new Binary(num, 0, "-");
			} else {
				val = token;
				return new Binary(-1, id_map(), val);
			}
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			while (is_digit()) {
				concat();
				ch_num++;
				getChar();
			}

			if (character == '.') {
				concat();
				ch_num++;
				getChar();

				if (!continue_int_map()) {
					return error();
				}
				getChar();
			}

			if (character == 'E') {
				return integer_after_E_map();
			} else {
				retract();
				return new Binary(-2, -1, token);
			}

		case '{':
			ch_num++;
			return new Binary(121, -1, "-");
		case '}':
			ch_num++;
			return new Binary(122, -1, "-");
		case '[':
			ch_num++;
			return new Binary(123, -1, "-");
		case ']':
			ch_num++;
			return new Binary(124, -1, "-");
		case ';':
			ch_num++;
			return new Binary(125, -1, "-");
		case ',':
			ch_num++;
			return new Binary(126, -1, "-");
		case '.':
			ch_num++;
			return new Binary(127, -1, "-");
		case '(':
			ch_num++;
			return new Binary(128, -1, "-");
		case ')':
			ch_num++;
			return new Binary(129, -1, "-");
		case ':':
			ch_num++;
			return new Binary(130, -1, "-");
		case '/':
			ch_num++;
			getChar();
			if (character == '*') {
				ch_num++;
				getChar();
				jump('*');
				getChar();
				while (character != '/') {
					jump('*');
					getChar();
				}
				ch_num++;
				return new Binary(131, -1, "-");
			} else if (character == '=') {
				ch_num++;
				return new Binary(223, -1, "-");
			} else if (character == '/') {
				ch_num++;
				getChar();
				jump('\n');
				return new Binary(134, -1, "-");
			} else {
				retract();
				return new Binary(213, -1, "-");
			}
		case '#':
			ch_num++;
			return new Binary(132, -1, "-");
		case '"':
			ch_num++;
			return new Binary(135, -1, "-");
		case '\'':
			ch_num++;
			return new Binary(136, -1, "-");
		case '*':
			ch_num++;
			getChar();
			if (character == '/') {
				ch_num++;
				return new Binary(133, -1, "-");
			} else if (character == '=') {
				ch_num++;
				return new Binary(222, -1, "-");
			} else {
				retract();
				return new Binary(212, -1, "-");
			}
		case '+':
			ch_num++;
			getChar();
			if (character == '=') {
				ch_num++;
				return new Binary(221, -1, "-");
			} else if (character == '+') {
				ch_num++;
				return new Binary(232, -1, "-");
			} else {
				retract();
				return new Binary(210, -1, "-");
			}
		case '-':
			ch_num++;
			getChar();
			if (character == '=') {
				ch_num++;
				return new Binary(220, -1, "-");
			} else if (character == '-') {
				ch_num++;
				return new Binary(233, -1, "-");
			} else {
				retract();
				return new Binary(211, -1, "-");
			}
		case '%':
			ch_num++;
			getChar();
			if (character == '=') {
				ch_num++;
				return new Binary(226, -1, "-");
			} else {
				retract();
				return new Binary(214, -1, "-");
			}
		case '>':
			ch_num++;
			getChar();
			if (character == '=') {
				ch_num++;
				return new Binary(217, -1, "GE");
			} else if (character == '>') {
				ch_num++;
				return new Binary(236, -1, "-");
			} else {
				retract();
				return new Binary(215, -1, "GT");
			}
		case '<':
			ch_num++;
			getChar();
			if (character == '=') {
				ch_num++;
				return new Binary(218, -1, "LE");
			} else if (character == '<') {
				ch_num++;
				return new Binary(235, -1, "-");
			} else {
				retract();
				return new Binary(216, -1, "LT");
			}
		case '=':
			ch_num++;
			getChar();
			if (character == '=') {
				ch_num++;
				return new Binary(219, -1, "EQ");
			} else {
				retract();
				return new Binary(225, -1, "assign-op");
			}
		case '!':
			ch_num++;
			getChar();
			if (character == '=') {
				ch_num++;
				return new Binary(224, -1, "NE");
			} else {
				retract();
				return new Binary(231, -1, "-");
			}
		case '&':
			ch_num++;
			getChar();
			if (character == '&') {
				ch_num++;
				return new Binary(228, -1, "-");
			} else {
				retract();
				return new Binary(227, -1, "-");
			}
		case '|':
			ch_num++;
			getChar();
			if (character == '|') {
				ch_num++;
				return new Binary(230, -1, "-");
			} else {
				retract();
				return new Binary(229, -1, "-");
			}
		case '~':
			ch_num++;
			return new Binary(234, -1, "-");
		case '?':
			ch_num++;
			return new Binary(237, -1, "-");
		case '@':
			return new Binary(-3, -1, "-");
		case '\n':
			line++;
			return new Binary(-3, -1, "-");

		default:
			concat();
			ch_num++;
			return error();
		}
	}

	public static void main(String[] args) throws IOException {
		bianyi bianyi = new bianyi();

		bianyi.inputStr = "";
		bianyi.keyWord_init();
		bianyi.bound_init();
		bianyi.Operator_init();
		bianyi.id.clear();
		bianyi.index = 0;
		bianyi.character = ' ';
		bianyi.token = "";

		File filename = new File("testProgram.c");
		InputStreamReader file = new InputStreamReader(new FileInputStream(filename));
		BufferedReader input = new BufferedReader(file);
		String line = input.readLine();
		while (line != null) {
			bianyi.inputStr = bianyi.inputStr + line + '\n';
			line = input.readLine();
		}
		Binary word = new Binary(0, 0, "-");
		// 循环进行词法分析直到识别所有单词符号
		System.out.println("\n------------------------识别结果------------------------");
		while (bianyi.index < bianyi.inputStr.length()) {
			word = bianyi.Analyzer();
			if (word.category == -2) {
				bianyi.num_word_num++;
				System.out.println("识别单词:\t(num\t" + word.value + ")");
			} else if (word.category == -1) {
				bianyi.id_word_num++;
				System.out.println("识别单词:\t(id\t" + word.index + ")");
			} else if (word.category >= 0 && word.category <= 54) {
				bianyi.keyword_num++;
				System.out.println("识别单词:\t(" + bianyi.keyWord[word.category] + "\t" + word.value + ")");
			} else if (word.category >= 121 && word.category <= 136) {
				bianyi.bound_word_num++;
				System.out.println("识别单词:\t(" + bianyi.Boundary[word.category] + "\t" + word.value + ")");
				if (word.category == 131) {
					bianyi.bound_word_num++;
					System.out.println("识别单词:\t(" + bianyi.Boundary[133] + "\t" + "-" + ")");
				}
			} else if (word.category >= 210 && word.category <= 237) {
				bianyi.operater_word_num++;
				System.out.println("识别单词:\t(" + bianyi.Operator[word.category] + "\t" + word.value + ")");
			} else if (word.category == -3) {

			}
		}
		System.out.println("\n总行数：\t" + (bianyi.line - 1) + "\t字符总数：\t" + bianyi.ch_num);
		System.out.println("\n各类单词个数：");
		System.out.println("id数量:\t" + bianyi.id_word_num);
		System.out.println("数字数量:\t" + bianyi.num_word_num);
		System.out.println("关键字数量:\t" + bianyi.keyword_num);
		System.out.println("分隔符数量:\t" + bianyi.bound_word_num);
		System.out.println("操作符数量:\t" + bianyi.operater_word_num);

	}
}
