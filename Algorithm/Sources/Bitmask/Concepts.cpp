﻿// bitmask

// 1. 매우 빠른 시간에 동작한다.
// 2. 간결하게 코드를 작성할 수 있다.
// 3. 메모리 절약이 가능하다.
// 4. 중첩 컨테이너를 단순 컨테이너로 대체할 수 있다.
// ex) map<vector<bool>, int>  ->  vector<int>
// 5. 집합 개념으로 활용될 수 있고, 집합 연산(합집합, 교집합, 차집합 ..)이 가능하다.

// 주의할 점
// 1. 항상 연산자 우선순위에 유의하여야 한다.
// 2. 상수 범위 오버플로우로 인한 문제
// 3. N-비트 크기의 변수를 N-비트 이상 시프트 연산하는 경우

// 비트마스크 문제 1.
// 타겟 넘버 (bitmask)
// https://programmers.co.kr/learn/courses/30/lessons/43165


// 비트마스크 문제 2.
// 후보키
// https://programmers.co.kr/learn/courses/30/lessons/42890