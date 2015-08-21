# 소개
**Stick** 은 어느 플랫폼에나 간단하게 적용할 수 있는 실시간 랭킹 서비스입니다. [Redis](http://redis.io)와 [FastCGI](http://fastcgi), 그리고 C++로 개발되어 대용량의 데이터도 속도 저하 없이 빠르게 처리할 수 있고, 순간적인 트래픽 증가에도 문제 없이 대응합니다. 개발자는 이제 더 이상 랭킹 구현을 위해 고민할 필요가 없습니다. 단지 **Stick** 에 정보를 보내고, 필요할 때 API를 호출하여 순위를 확인하면 됩니다.

# 시작하기

### API 키 발급

1. **Stick** 계정을 [생성](http://172.16.101.146:8080/register)하세요.
2. 로그인 후 우측 상단의 *API 관리* 메뉴를 선택하세요.
3. 적절한 랭킹 요소 이름을 입력한 뒤, *요소 추가* 버튼을 누르세요.
4. 해당 요소에 대한 키가 생성됩니다.

# 레코드 관리

### 생성
랭킹 요소를 생성한 다음, 해당 요소에 레코드를 추가할 수 있습니다.

| 키       | 타입    | 위치  | 설명                                               |
|----------|--------|------|---------------------------------------------------|
| api_key | string | url  | 관리 페이지에서 생성한 랭킹 요소의 키입니다.
| id      | string | body | 레코드의 고유한 아이디입니다.
| score   | int    | body | 랭킹에 사용할 레코드의 점수입니다. 랭킹은 내림차순으로 정렬됩니다.

##### Request
```
POST /user/your_api_key HTTP/1.1
Host: stick.rest:9000
Content-Type: text/json
{
    "id":"record_id"
    "score":999
}
```

##### Response
```
HTTP/1.1 201 Created
Content-Type: text/json
{
    "result":"success"
}
```

### 조회
레코드의 `id`를 이용하여 해당 레코드의 `score`를 조회할 수 있습니다.

| 키       | 타입    | 위치 | 설명
|----------|--------|-----|----------------------------------------------------|
| api_key | string | url | 관리 페이지에서 생성한 랭킹 요소의 키입니다.
| id      | string | url | 레코드의 고유한 아이디입니다.

##### Request
```
GET /user/your_api_key/record_id HTTP/1.1
Host: stick.rest:9000
```

##### Response
```
HTTP/1.1 302 Found
Content-Type: text/json
{
    "score":819324
}
```

### 수정
특정 레코드의 `score`를 갱신할 수 있습니다.

| 키       | 타입    | 위치  | 설명                                               |
|----------|--------|------|---------------------------------------------------|
| api_key | string | url  | 관리 페이지에서 생성한 랭킹 요소의 키입니다.
| id      | string | body | 레코드의 고유한 아이디입니다.
| score   | int    | body | 랭킹에 사용할 레코드의 점수입니다. 랭킹은 내림차순으로 정렬됩니다.

##### Request
```
PUT /user/your_api_key HTTP/1.1
Host: stick.rest:9000
Content-Type: text/json
{
    "id":"record_id"
    "score":999
}
```

##### Response
```
HTTP/1.1 200 OK
Content-Type: text/json
{
    "result":"success"
}
```

### 삭제
특정 레코드를 삭제할 수 있습니다.

| 키       | 타입    | 위치 | 설명                                                |
|---------|--------|-----|----------------------------------------------------|
| api_key | string | url | 관리 페이지에서 생성한 랭킹 요소의 키입니다.
| id      | string | url | 레코드의 고유한 아이디입니다.

##### Request
```
DELETE /user/your_api_key/record_id HTTP/1.1
Host: stick.rest:9000
```

##### Response
```
HTTP/1.1 200 OK
Content-Type: text/json
{
    "result":"success"
}
```

# 랭킹

### 랭킹 가져오기
레코드의 `id`를 이용하여 해당 레코드의 순위를 조회할 수 있습니다.

| 키       | 타입    | 위치 | 설명                                                |
|----------|--------|-----|----------------------------------------------------|
| api_key | string | url | 관리 페이지에서 생성한 랭킹 요소의 키입니다.
| id      | string | url | 레코드의 고유한 아이디입니다.

##### Request
```
GET /ranking/your_api_key/record_id HTTP/1.1
Host: stick.rest:9000
```

##### Response
```
HTTP/1.1 200 OK
Content-Type: text/json
{
    "rank":"2341"
}
```

### 랭킹 페이지 가져오기
받아올 순위의 범위를 정해 해당 구간의 레코드 목록을 가져올 수 있습니다. 한 번의 요청으로 최대 100개의 유저 목록을 받아올 수 있습니다.

| 키       | 타입    | 위치 | 설명                                                |
|----------|--------|-----|----------------------------------------------------|
| api_key | string | url | 관리 페이지에서 생성한 랭킹 요소의 키입니다.
| start   | string | url | 받아 올 구간의 시작 지점입니다.
| end     | string | url | 받아 올 구간의 끝 지점입니다.

##### Request
```
GET /ranking/your_api_key/1/3 HTTP/1.1
Host: stick.rest:9000
```

##### Response
```
HTTP/1.1 200 OK
Content-Type: text/json
{
    "test_record_1" : {
        "score":33891,
        "rank":1
    },
    "test_record_2" : {
        "score":23459,
        "rank":2
    },
    "test_record_3" : {
        "score":975,
        "rank":3
    },

}
```

# Introduce
**Stick** is a real-time ranking service which can be easily used for any kind of platform. Because it is developed using [Redis](http://redis.io), [FastCGI](http://fastcgi), and C++, it can handle large amount of data without performance degradation and deal with immediate increase in network traffic without any problems. Now developers are not need to be concerned about how to develop a ranking system. Just send your data to **Stick**, and call API when you need a ranking of your data.

# Getting started

### Acquiring API keys

1. [Create](http://172.16.101.146:8080/register) your **Stick** accout.
2. Select *API manage* menu after sign in.
3. Enter suitable ranking property name, and press *add property* button.
4. The API Keys will be automatically generated.

# Record management
After creating ranking property, you can add record which have same property you have created previously.

| Key     | Type   | Location | Description                                  |
|---------|--------|----------|----------------------------------------------|
| api_key | string | url      | Ranking property key you created in dashboard.
| id      | string | body     | Unique ID of the record.
| score   | int    | body     | Score of the record which is used to determine the ranking. Ranking will order by descending score.

##### Request
```
POST /user/your_api_key HTTP/1.1
Host: stick.rest:9000
{
    "id":"record_id"
    "score":999
}
```

##### Response
```
HTTP/1.1 201 Created
Content-Type: text/json
{
    "result":"success"
}
```

### Read
You can request a score of the record by using record id.

| Key     | Type   | Location | Description                                  |
|---------|--------|----------|----------------------------------------------|
| api_key | string | url      | Ranking property key you created in dashboard.
| id      | string | url      | Unique ID of the record.

##### Request
```
GET /user/your_api_key/record_id HTTP/1.1
Host: stick.rest:9000
```

##### Response
```
HTTP/1.1 302 Found
Content-Type: text/json
{
    "score":819324
}
```

### Modify
You can renew the score of the record.

| Key     | Type   | Location | Description                                  |
|---------|--------|----------|----------------------------------------------|
| api_key | string | url      | Ranking property key you created in dashboard.
| id      | string | body     | Unique ID of the record.
| score   | int    | body     | Score of the record which is used to determine the ranking. Ranking will order by descending score.

##### Request
```
PUT /user/your_api_key HTTP/1.1
Host: stick.rest:9000
{
    "id":"record_id"
    "score":999
}
```

##### Response
```
HTTP/1.1 200 OK
Content-Type: text/json
{
    "result":"success"
}
```

### Delete
You can delete a specific record.

| Key     | Type   | Location | Description                                  |
|---------|--------|----------|----------------------------------------------|
| api_key | string | url      | Ranking property key you created in dashboard.
| id      | string | url      | Unique ID of the record.

##### Request
```
DELETE /user/your_api_key/record_id HTTP/1.1
Host: stick.rest:9000
```

##### Response
```
HTTP/1.1 200 OK
Content-Type: text/json
{
    "result":"success"
}
```

# Ranking

### Get ranking
By using record `id`, you can refer us to send the record's rank.

| Key     | Type   | Location | Description                                  |
|---------|--------|----------|----------------------------------------------|
| api_key | string | url | Ranking property key you created in dashboard.
| id      | string | url | Unique ID of the record.

##### Request
```
GET /ranking/your_api_key/record_id HTTP/1.1
Host: stick.rest:9000
```

##### Response
```
HTTP/1.1 200 OK
Content-Type: text/json
{
    "rank":"2341"
}
```

### Get ranking pages
You can get get a list of records by assigning the range of rankings. The maximum size of the list per request is 100.

| Key     | Type   | Location | Description                                  |
|---------|--------|----------|----------------------------------------------|
| api_key | string | url | Ranking property key you created in dashboard.
| start   | string | url | The starting point of the range of rankings.
| end     | string | url | The ending point of the range of rankings.

##### Request
```
GET /ranking/your_api_key/1/3 HTTP/1.1
Host: stick.rest:9000
```

##### Response
```
HTTP/1.1 200 OK
Content-Type: text/json
{
    "test_record_1" : {
        "score":33891,
        "rank":1
    },
    "test_record_2" : {
        "score":23459,
        "rank":2
    },
    "test_record_3" : {
        "score":975,
        "rank":3
    },

}
```
