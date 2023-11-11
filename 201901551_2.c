#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char save_palindrome[100]; // 가장 긴 회문을 저장할 충분히 큰 배열
int maxlen = 0; // 가장 긴 회문의 길이

// 길이가 n인 문자열 생성 함수
char* makeString(int n) {
    char* str = (char *)malloc(n * sizeof(char));

    srand(time(NULL));

    for (int i = 0 ; i < n ; i++) {
        str[i] = rand() % 26 + 'A';
    }

    return str;
}

// 주어진 문자열에서 가장 긴 연속된 회문을 찾는 함수
int palindrome(char* s, int i, int j) { 
    int n = j - i; // 문자열의 실제 길이 계산
    int dp[n][n]; // 동적 계획법을 위한 배열 초기화
    memset(dp, 0, sizeof(dp)); // dp 테이블의 모든 값을 0으로 초기화
    int maxLen = 1; // 회문의 최대 길이를 저장할 변수
    int start = 0;  // 가장 긴 회문의 시작 인덱스

    // 모든 단일 문자는 회문이므로 길이는 1
    for (int x = 0; x < n; x++) {
        dp[x][x] = 1;
    }

    // 연속된 두 문자에 대한 회문 검사
    for (int x = 0; x < n - 1; x++) {
        if (s[x] == s[x + 1]) {
            dp[x][x + 1] = 1;
            start = x;
            maxLen = 2;
        }
    }

    // 길이가 3 이상인 부분 문자열에 대해 회문 검사
    // 여기서 길이를 3부터 시작하여 모든 가능한 길이에 대해 반복한다.
    // 시간 복잡도: O(n^2) - 여기서 n은 문자열의 길이, 모든 가능한 부분 문자열에 대해 회문 검사를 수행한다.
    for (int len = 3; len <= n; len++) {
        // 시작 인덱스 x에 대해 반복
        for (int x = 0; x < n - len + 1; x++) {
            // 종료 인덱스 y는 시작 인덱스 x와 부분 문자열의 길이 len에 의해 결정된다.
            int y = x + len - 1;
            // 부분 문자열 s[x...y]가 회문인지 검사
            if (s[x] == s[y] && dp[x + 1][y - 1]) {
                dp[x][y] = 1;
                start = x;
                maxLen = len;
            }
        }
    }

    strncpy(save_palindrome, s + start, maxLen); // 가장 긴 회문을 save_palindrome 배열에 복사
    save_palindrome[maxLen] = '\0'; // 문자열의 마지막을 나타내는 널 문자를 추가

    return maxLen;
}

int main() {
    char* str = makeString(15);
    maxlen = palindrome(str, 0, strlen(str)); // palindrome 함수 호출 후 maxlen에 리턴 값 저장
    printf("'%s'에서는 %s가 긴 연속된 회문이며 그 길이는 %d 이다.\n", str, save_palindrome,maxlen); // 출력
    free(str);
    
    return 0;
}