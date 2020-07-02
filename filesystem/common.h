//
// Created by linux on 6/30/20.
//

#ifndef MODULE_2_COMMON_H
#define MODULE_2_COMMON_H

#define ERROR		(-1)
#define BADFD		(-2)

#define MAXFNAME	10
#define MAXARG		10
#define MAXWORD		20
#define MAXFD		20
#define MAXVAR		50
#define MAXNAME		20

#define TRUE		1
#define FALSE		0

typedef int BOOLEAN;

// 파일의 타입을 결정하는 열거형 변수
typedef enum
{
    S_WORD,
    S_BAR,
    S_AMP,
    S_SEMI,
    S_GT,
    S_GTGT,
    S_LT,
    S_NL,
    S_EOF
} SYMBOL;


#endif //MODULE_COMMON_H
