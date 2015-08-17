## 소개
**Stick** 은 어느 플랫폼에나 간단하게 적용할 수 있는 실시간 랭킹 서비스입니다. [Redis](http://redis.io)와 [FastCGI](http://fastcgi), 그리고 C++로 개발되어 대용량의 데이터도 속도 저하 없이 빠르게 처리할 수 있고, 순간적인 트래픽 증가에도 문제 없이 대응합니다. 개발자는 이제 더 이상 랭킹 구현을 위해 고민할 필요가 없습니다. 단지 **Stick** 에 정보를 보내고, 필요할 때 API를 호출하여 순위를 확인하면 됩니다.

## 시작하기

#### API 키 발급
**Stick** 계정을 생성하세요. 계정을 생성하기만 하면 API 키가 자동으로 발급됩니다.

#### 랭킹 요소 생성하기
누나 빨리 만들어 주세요 ㅠㅠ

## 레코드 관리

#### 생성
랭킹 요소를 생성한 다음, 해당 요소에 유저를 추가할 수 있습니다.

|    키   |   타입  |                         설명                         |
|--------|--------|------------------------------------------------------|
| member | string | 레코드의 고유한 아이디입니다.                              |
| score  | int    | 랭킹에 사용할 레코드의 점수입니다. 랭킹은 내림차순으로 정렬됩니다. |

##### [ Request ]
```
GET /ranking/your_api_key HTTP/1.1
Host: stick.rest:9000
```

##### [ Response ]
```
HTTP/1.1 201 Created
Content-Type: text/json
{
    "result":"success"
}
```

#### 읽기

##### [ Request ]
```
GET /ranking/your_api_key/member HTTP/1.1
Host: stick.rest:9000
```

##### [ Response ]
```
HTTP/1.1 302 Found
Content-Type: text/json
{
    "rank":819324
}
```

#### 수정

#### 삭제

## 랭킹

#### 랭킹 가져오기

#### 랭킹 페이지 가져오기


## Introduce
**Stick** is a real-time ranking service which can be easily used for any kind of platform. Because it is developed using [Redis](http://redis.io), [FastCGI](http://fastcgi), and C++, it can handle large amount of data without performance degradation and deal with immediate increase in network traffic without any problems. Now developers are not need to be concerned about how to develop a ranking system. Just send your data to **Stick**, and call API when you need a ranking of your data.

## Getting started

#### Acquiring API keys
Create your **Stick** accout. API keys will be automatically generated for you after signing up.

#### Create ranking properties

## Record management

#### Create

#### Read

#### Modify

#### Delete

## Ranking

#### Get ranking

#### Get ranking pages
