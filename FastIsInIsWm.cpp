#include <stdio.h>
#include <conio.h>
#include <string>
#include <vector>

using namespace std;

int isin(char *text, char *subtext, int nPos = 0)
{
	int nTextLen = strlen(text),
		nSubLen = strlen(subtext),
		nStateFail = 0,
		i = nPos - 1,
		j = 0;

	while (++i < nTextLen)
	{
		if (i + nSubLen > nTextLen)
			return -1;
		if (text[i] == subtext[0])
		{
			j = 0;
			while (++j < nSubLen)
				if (text[i + j] != subtext[j])
					break;
			if (j == nSubLen)
				return i - 1;
		}
	}
	return -1;
}

int iswm(char *str, char *substr)
{
	int nLenStr = strlen(str),
		nLenSubstr = strlen(substr),
		nPosStr = 0,
		nPosSubstr = 0;

	while (1)
	{
		// всякие условия выхода по завершению какой-то строки
		if (nPosStr >= nLenStr) {
			if (nPosSubstr < nLenSubstr)
				return 0;
			else
				return 1;
		}
		if (nPosSubstr >= nLenSubstr)
		{
			if (substr[nLenSubstr - 1] == '*' || nPosStr >= nLenStr)
				return 1;
			else
				return 0;
		}
		
		// если ждём одиночный символ - пропускаем значит
		if (substr[nPosSubstr] == '?')
		{
			nPosSubstr++;
			nPosStr++;
			continue;
		}

		// переходим в поиск следующих символов
		if (substr[nPosSubstr] == '*')
		{
			nPosSubstr++;
			int nMustBeSymbols = 0;
			while (nPosSubstr < nLenSubstr && (substr[nPosSubstr] == '*' || substr[nPosSubstr] == '?'))
			{
				if (substr[nPosSubstr] == '?')
					nMustBeSymbols++;
				nPosSubstr++;
			}

			if (nPosSubstr == nLenSubstr)
				return nLenStr - nPosStr >= nMustBeSymbols;

			int nEndPos = nPosSubstr;	// это - окончание символов любых
			while (nEndPos < nLenSubstr && substr[nEndPos] != '?' && substr[nEndPos] != '*')
				nEndPos++;

			int nTmpLen = nEndPos - nPosSubstr;
			char *tmpStr = new char[nTmpLen];
			memcpy(tmpStr, substr + nPosSubstr, nTmpLen);
			tmpStr[nTmpLen] = '\0';
			// ищем вхождение наших символов из substr в str
			int nFindPos = isin(str, tmpStr, nPosStr);

			// если не нашлось или мало символов, которые должны быть - выходим
			if (nFindPos == -1 || nFindPos - nPosStr < nMustBeSymbols)
				return 0;

			// если всё хорошо - перемещаемся на новую позицию и идём дальше
			nPosStr = nFindPos + nTmpLen;
			nPosSubstr = nEndPos;

			printf("%d\n", nFindPos);
			continue;
		}

		if (str[nPosStr] != substr[nPosSubstr])
			return 0;
		nPosStr++;
		nPosSubstr++;
	}
	return 1;
}

int main()
{
	printf("%d\n", iswm("sta44444dfs3333fa1111fd2222FDD", "sta44444dfs3333fa*D?"));
	_getch();
	return 0;
}