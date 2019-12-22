#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*
* �������Ҫ˼·��:�ѹ̶������е��Ӵ�(����Ҫ��)���ŵ�һ���ṹ�������У�
* ��֮ǰ�ȼ��һ�½ṹ������û�������¼���еĻ����Ͱ����Ӧ��valֵ��1��
* ����ֻ��ͨ��11��������
*/

typedef struct _HashMap {
	char key[26 + 1];
	int val;
}HashMap;

int maxFreq(char * s, int maxLetters, int minSize, int maxSize){

	int i;
	int k;
	int letters = 0;
	int result = 0;
	char map[26 + 1] = {0};
	HashMap* counterMap = NULL;	
	char* tmpSaveStr = NULL;
	int hashCounter = 0;
	
	if (s == NULL || maxLetters >= maxSize) {
		return 0;
	}
	tmpSaveStr = (char*)malloc(1 + strlen(s) * sizeof(char));
	counterMap = (HashMap*)malloc(strlen(s) * sizeof(HashMap));
	if (counterMap == NULL || tmpSaveStr == NULL) {
		return 0;
	}
	memset(counterMap, 0, strlen(s) * sizeof(HashMap));
	memset(tmpSaveStr, 0, 1 + strlen(s) * sizeof(char));
	memcpy(tmpSaveStr, s, strlen(s));

	
	for (i = 0; i < strlen(s); i++) {
		map[s[i] - 'a']++;
	}
	for (i = 0; i < 27; i++) {
		if (map[i] != 0) {
			letters++;
		}
	}
	if (letters == 1 && maxLetters == 1) {
		result = strlen(s) / minSize + strlen(s) % minSize;
		return result;   /* ���ﴦ��ȫ��һ�����ַ���� */
	} else {
		letters = 0;
		memset(map, 0, 27);
	}

	for (i = 0; i < strlen(s); i++) {
		letters = 0;
		for (k = i; k < (i + minSize) && k < strlen(s); k++) {
			if ((s[k] - 'a') < 0) {
				return 0;
			}
			if (map[s[k] - 'a'] == 1) {
				continue;
			}
			map[s[k] - 'a']++;
			if (map[s[k] - 'a'] == 1) {
				letters++;
			} else {
				map[s[k] - 'a']--;
			}
		}
		
		if ((letters <= maxLetters) && (i + minSize <= strlen(s))) {
			if (hashCounter == 0) {
				memcpy(counterMap[hashCounter].key, &tmpSaveStr[i], minSize);
				counterMap[hashCounter].val = 1;
				hashCounter++;			
			} else {
				for (i = 0; i < hashCounter; i++) {
					if (memcmp(counterMap[hashCounter].key, &tmpSaveStr[i], 
						minSize) == 0) {
						counterMap[hashCounter].val++;
					}
				}
				hashCounter++;
				memcpy(counterMap[hashCounter].key, &tmpSaveStr[i], minSize);
				counterMap[hashCounter].val = 1;			
		    }
		} else {
			break;
		}
	}
	
	result = counterMap[0].val;
	for (i = 1; i < hashCounter; i++) {
		if (result < counterMap[i].val) {
			result = counterMap[i].val;
		}
	}
	return result;
}

int main(void)
{
	char* str = "aaaa";
	int result = maxFreq(str, 2, 3, 3);
	printf("\r\n the result=%d", result);
}
