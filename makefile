all:sever client

sever:sever.c LinkList.c
	gcc sever.c LinkList.c -o sever


client:client.c LinkList.c
	gcc client.c LinkList.c -o client