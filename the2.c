#include <stdio.h>
#include <stdlib.h>
#include <strings.h>




struct node {
    int data;
    struct node *next;
};
struct message_node{
    int sender_id;
    int topic_id;
    int message_id;
    struct message_node *next;
};
struct topic_node{
    char *topic_name;
    int topic_id;
    struct node *follower_list;
    struct topic_node *next;


};
struct user_node{
    char *user_name;
    int user_id;
    struct node *followed_topics;
    struct message_node *inbox;
    struct user_node *next;

};



typedef struct node node;
typedef struct message_node message_node;
typedef struct topic_node topic_node;
typedef struct user_node user_node;


void prin(user_node **users);
void removefollowed(user_node **users,int us_id, int  top_id,topic_node **topnode);
void unsubscribe(user_node **users,char *username, char *topname,topic_node **topnode);
void del_messages(user_node **users,int us_id,int mes_id);
void del_user(user_node **users,char *username,topic_node **topnode);
void send(message_node **mes_node,char *username,char *topname,user_node **users,topic_node **topnode);
void add_mine_mes_box( user_node **users,int us_id,int mes_id,int sender_id,int top_id);
int add_message(message_node **messages,int us_id,int top_id);
void add_follewer_list(topic_node **topics,int top_i,user_node **users,int us_id);
void add(user_node **users,char *username,int id_num);
void subscribe(topic_node **topnode,char *top,char *username,user_node **users);
int find_userid(user_node **users,char *username);
int find_topicid(topic_node **topiks,char *top);
void add_top(topic_node **topics,char *topname);



int main() {
    void add(user_node **users,char *username,int id_num);
    user_node   *usernode;
    void subscribe(topic_node **topnode,char *top,char *username,user_node **users);
    topic_node *topnode;
    message_node *mesnode;
    int add_id;
    char  *str,*val1,*val2;
    int i = 0;
    int k = 0;
    int p = 0;
    char *lis[400];
    char *lis2[400];

    char tut[2][200][20];


    topnode = NULL;
    usernode = NULL;
    mesnode = NULL;



    add_id = 1;



    str = (char *) malloc(sizeof(char)*60);
    val1 = (char *) malloc(sizeof(char)*20);
    val2 = (char *) malloc(sizeof(char)*20);

    while(fgets(str,55,stdin) != NULL){

        if(str[0] == 'A'){
            i=4;
            while(str[i] != '\n'){

                tut[0][p][i-4] = str[i];
                i++;

            }
            tut[0][p][i-4] = '\0';


            lis[p] = tut[0][p];

            add(&usernode,tut[0][p],add_id);
            add_id++;


        }

        if(str[0] == 'S' && str[1] == 'U'){
            i=10;
            k=0;
            while(str[i] != ' '){

                tut[0][p][i-10] = str[i];
                i++;

            }
            tut[0][p][i-10] = '\0';
            i++;
            while(str[i] != '\n'){

                tut[1][p][k] = str[i];
                i++;
                k++;

            }

            tut[1][p][k] = '\0';

            lis[p] = tut[0][p];
            lis2[p] = tut[1][p];

            subscribe(&topnode,tut[1][p],tut[0][p],&usernode);

        }
        if(str[0] == 'S' && str[1] == 'E'){
            i=5;
            k=0;
            while(str[i] != ' '){

                tut[0][p][i-5] = str[i];
                i++;

            }
            tut[0][p][i-5] = '\0';
            i++;
            while(str[i] != '\n'){

                tut[1][p][k] = str[i];
                i++;
                k++;

            }

            tut[1][p][k] = '\0';



            lis2[p] = tut[1][p];
            lis[p] = tut[0][p];
            send(&mesnode,tut[0][p],tut[1][p],&usernode,&topnode);
        }
        if(str[0] == 'U' && str[1] == 'N'){
            i=12;
            k=0;
            while(str[i] != ' '){

                tut[0][p][i-12] = str[i];
                i++;

            }
            tut[0][p][i-12] = '\0';
            i++;
            while(str[i] != '\n'){

                tut[1][p][k] = str[i];
                i++;
                k++;

            }

            tut[1][p][k] = '\0';

            lis2[p] = tut[1][p];
            lis[p] = tut[0][p];

            unsubscribe(&usernode,tut[0][p],tut[1][p],&topnode);

        }
        if(str[0] == 'D'){
            i=11;
            while(str[i] != '\n'){

                tut[0][p][i-11] = str[i];
                i++;

            }
            tut[0][p][i-11] = '\0';

            lis[p] = tut[0][p];
            del_user(&usernode,tut[0][p],&topnode);
        }


    free(str);
    free(val1);
    free(val2);

        str = (char *) malloc(sizeof(char)*60);
        val1 = (char *) malloc(sizeof(char)*20);
        val2 = (char *) malloc(sizeof(char)*20);

        p++;
    }

    prin(&usernode);
    return 0;
}
void prin(user_node **users){
    message_node *tem_mes;
    if ((*users) == NULL){


    }else {
        while ((*users)->next != NULL) {

            printf("%d:", (*users)->user_id);
            if ((*users)->inbox == NULL) {

            } else {
                tem_mes = (*users)->inbox;
                while (tem_mes->next != NULL) {
                    printf(" %d", tem_mes->message_id);
                    tem_mes = tem_mes->next;
                }
                printf(" %d", tem_mes->message_id);
            }
            printf("\n");

            (users) = &((*users)->next);

        }
        printf("%d:", (*users)->user_id);
        if ((*users)->inbox == NULL) {

        } else {
            tem_mes = (*users)->inbox;
            while (tem_mes->next != NULL) {
                printf(" %d", tem_mes->message_id);
                tem_mes = tem_mes->next;
            }
            printf(" %d", tem_mes->message_id);
        }

        printf("\n");
    }
}
void removefollowed(user_node **users,int us_id, int  top_id,topic_node **topnode){




    node *temp,*temp2;

    while((*topnode)->topic_id != top_id){

        topnode = &((*topnode)->next);
    }
    if((*topnode)->follower_list == NULL){

    }else {
        temp = (*topnode)->follower_list;
        temp2 = (*topnode)->follower_list;


        if (temp->data == us_id) {
            if (temp->next == NULL) {
                (*topnode)->follower_list = NULL;
            } else {
                (*topnode)->follower_list = temp->next;
            }
        } else {
            if (temp == NULL || temp->next == NULL) {

            }else {
                temp = temp->next;
                while (temp->data != us_id) {
                    if (temp->next == NULL) return;
                    temp = temp->next;
                    temp2 = temp2->next;

                }
                if (temp->next == NULL) {
                    temp2->next = NULL;
                } else {
                    temp2->next = (temp->next);

                }
            }
        }
    }
}
void unsubscribe(user_node **users,char *username, char *topname,topic_node **topnode){
    int us_id,top_id;
    message_node *mes_tem;
    node *temp,*temp2;
    us_id = find_userid(users,username);
    top_id = find_topicid(topnode,topname);



    while((*topnode)->topic_id != top_id){

        topnode = &((*topnode)->next);
    }


    temp = (*topnode)->follower_list ;
    temp2 = (*topnode)->follower_list ;


    if(temp->data == us_id){
        if(temp->next == NULL){
            (*topnode)->follower_list = NULL;
        }else {
            temp = temp->next;
            (*topnode)->follower_list = temp;
        }
    }else {
        temp = temp->next;

        while (temp->data != us_id) {

            temp = temp->next;
            temp2 = temp2->next;

        }
        if(temp->next == NULL){
            temp2->next = NULL;
        }else{
            temp2->next = (temp->next);

        }
    }


    while ((*users)->user_id != us_id){

        (users) = &((*users)->next);
    }
    if((*users)->inbox == NULL){

    }else {
        mes_tem = (*users)->inbox;
        for (; mes_tem->next != NULL; mes_tem = mes_tem->next) {

            if (mes_tem->topic_id == top_id) {
                del_messages(users, us_id, mes_tem->message_id);

            }

        }
        if (mes_tem->topic_id == top_id) {
            del_messages(users, us_id, mes_tem->message_id);

        }
    }


}
void del_messages(user_node **users,int us_id,int mes_id){
    message_node **me_temp,**temp;
    int id,k;
    while((*users)->user_id !=us_id){


        (users) = &((*users)->next);

    }
    me_temp = &((*users)->inbox);
    temp = &((*users)->inbox);








    if((*me_temp)->message_id == mes_id){

        temp = &((*temp)->next);

        *me_temp = *temp;


    }else{

        id = 1;
        while((*me_temp)->message_id !=  mes_id){

            id++;
            (me_temp) = &((*me_temp)->next);



        }
        if((*me_temp)->next == NULL){
            for (k = 1; k < id - 1; k++) {

                temp = &((*temp)->next);

            }
            (*temp)->next = NULL;

        }else {
            for (k = 1; k < id - 1; k++) {

                temp = &((*temp)->next);

            }
            (me_temp) = &((*me_temp)->next);
            (*temp)->next = (*me_temp);
        }
    }

}
void del_user(user_node **users,char *username,topic_node **topnode){
    user_node **temp,**tempo;
    message_node *keep;
    node *tem;
    int us_id,id,k;
    us_id = find_userid(users,username);


       tempo = users;

       while((*tempo)->next != NULL){

            if((*tempo)->inbox != NULL) {
                keep = (*tempo)->inbox;
                while (keep->next != NULL) {

                    if (keep->sender_id == us_id) del_messages(users, (*tempo)->user_id, keep->message_id);

                    keep = keep->next;
                }
                if (keep->sender_id == us_id) del_messages(users, (*tempo)->user_id, keep->message_id);


            }
           (tempo) = &((*tempo)->next);
       }

    if((*tempo)->inbox != NULL) {
        keep = (*tempo)->inbox;
        while (keep->next != NULL) {

            if (keep->sender_id == us_id) del_messages(users, (*tempo)->user_id, keep->message_id);

            keep = keep->next;
        }
        if (keep->sender_id == us_id) del_messages(users, (*tempo)->user_id, keep->message_id);


    }

    temp = users;
    if((*users)->user_id ==us_id){


        tem = (*users)->followed_topics;
        if( (*users)->followed_topics == NULL){

        }else {
            while (tem->next != NULL) {

                removefollowed(users,us_id,tem->data,topnode);
                tem = tem->next;
            }
            removefollowed(users,us_id,tem->data,topnode);

        }




        temp = &((*temp)->next);

        *users = *temp;


    }else{

        id = 1;
        while((*users)->user_id !=us_id){

            id++;
            (users) = &((*users)->next);



        }
        tem = (*users)->followed_topics;
        if( (*users)->followed_topics == NULL){

        }else {
            while (tem->next != NULL) {

                removefollowed(users,us_id,tem->data,topnode);
                tem = tem->next;
            }
            removefollowed(users,us_id,tem->data,topnode);

        }

        if((*users)->next == NULL){
            for (k = 1; k < id - 1; k++) {

                temp = &((*temp)->next);

            }
            (*temp)->next = NULL;

        }else {
            for (k = 1; k < id - 1; k++) {

                temp = &((*temp)->next);

            }
            (users) = &((*users)->next);
            (*temp)->next = (*users);
        }
    }



}
void send(message_node **mes_node,char *username,char *topname,user_node **users,topic_node **topnode){

    int us_id,top_id, mes_id,i;
    topic_node **tempnode ;
    node **temp,*follow;
    tempnode =topnode;
    us_id = find_userid(users,username);
    top_id = find_topicid(topnode,topname);



    mes_id = add_message(mes_node, us_id,top_id);

    add_mine_mes_box(users,us_id, mes_id,us_id,top_id);

    for(i=1;i<top_id;i++){
        (tempnode) = &((*tempnode)->next);
    }


    if ((*tempnode)->follower_list == NULL){


    }else{
        temp = &((*tempnode)->follower_list);
        while((*temp)->next !=NULL){
            if((*temp)->data != us_id) add_mine_mes_box(users,(*temp)->data, mes_id,us_id,top_id);

            temp = &((*temp)->next);

        }
        if((*temp)->data != us_id) add_mine_mes_box(users,(*temp)->data, mes_id,us_id,top_id);

    }


}
void add_mine_mes_box( user_node **users,int us_id,int mes_id,int sender_id,int top_id){
    message_node **temp;
    message_node *messa = (message_node*) malloc(sizeof(message_node));
    int i;

    messa->topic_id = top_id;
    messa->sender_id = sender_id;
    messa->message_id = mes_id;
    messa->next = NULL;



    for(i=1;(*users)->user_id != us_id;i++){
        (users) = &((*users)->next);
    }



    if ((*users)->inbox == NULL){

        (*users)->inbox = messa;

    }else{
        temp = &((*users)->inbox);
        while((*temp)->next !=NULL){
            temp = &((*temp)->next);

        }
        (*temp)->next = messa;

    }

}
int add_message(message_node **messages,int us_id,int top_id){
    message_node *mess = (message_node*) malloc(sizeof(message_node));
    int id =1;

    mess->topic_id = top_id;
    mess->sender_id = us_id;
    mess->next = NULL;


    if (*messages != NULL){

        if((*messages)->next == NULL){
            mess->message_id = 2;
            id = 2;
            (*messages)->next = mess;


        }else{

            while( (*messages)->next != NULL){
                (messages) = &((*messages)->next);
                id++;

            }

            (*messages)->next = mess;

            (messages) = &((*messages)->next);
            (*messages)->message_id = id+1;
            id++;
        }
    }else{

        mess->message_id = 1;
        *messages = mess;

    }
    return id;
}
void add_follewer_list(topic_node **topics,int top_i,user_node **users,int us_id){
    int i,k;

    node *user = (node*) malloc(sizeof(node));
    node *topic = (node*) malloc(sizeof(node));

    node **temp;
    node **tempo;


    topic->data=top_i;
    topic->next = NULL;

    user->data=us_id;
    user->next = NULL;






    while((*topics)->topic_id != top_i){

        (topics) = &((*topics)->next);

    }
    while((*users)->user_id !=us_id){

        (users) = &((*users)->next);

    }

    if ((*topics)->follower_list == NULL){

        (*topics)->follower_list = user;

    }else{
        temp = &((*topics)->follower_list);
        while((*temp)->next !=NULL){
            temp = &((*temp)->next);

        }
        (*temp)->next = user;

    }


    if ((*users)->followed_topics == NULL){

        (*users)->followed_topics = topic;

    }else{
        tempo = &((*users)->followed_topics);
        while((*tempo)->next !=NULL){
            tempo = &((*tempo)->next);

        }
        (*tempo)->next = topic;

    }


}
void add(user_node **users,char *username,int id_num){
    user_node *user = (user_node*) malloc(sizeof(user_node));
    int id =1;

    user->user_name = username;
    user->followed_topics = NULL;
    user->inbox = NULL;
    user->next = NULL;


    if (*users != NULL){

        if((*users)->next == NULL){
            user->user_id = id_num;
            (*users)->next = user;


        }else{

            while( (*users)->next != NULL){
                (users) = &((*users)->next);
                id++;

            }

            (*users)->next = user;

            (users) = &((*users)->next);
            (*users)->user_id = id_num;
        }
    }else{

        user->user_id = id_num;
        *users = user;

    }

}
void subscribe(topic_node **topnode,char *top,char *username,user_node **users){

    int us_id,top_id;



    us_id = find_userid(users,username);
    top_id = find_topicid(topnode,top);



    if (top_id == -1){

        add_top(topnode,top);
        top_id = find_topicid(topnode,top);
        add_follewer_list(topnode,top_id,users,us_id);


    }else{
        add_follewer_list(topnode,top_id,users,us_id);

    }

}
int find_userid(user_node **users,char *username){


    while(strcmp( (*users)->user_name,username)){

        (users) = &((*users)->next);


    }
    return (*users)->user_id;
}
int find_topicid(topic_node **topiks,char *top){
    int id = 1;
    topic_node **topics;
    int st1,st2;
    topics = topiks;
    if (*topiks == NULL){

        return -1;
    }



    st1 = !strcmp( (*topiks)->topic_name,top);

    st2 =(*topiks)->next != NULL ;
    if(!st1 && !st2) return -1;
    if(st1) return 1;
    while(strcmp( (*topiks)->topic_name,top) && (*topiks)->next != NULL){
        (topiks) = &((*topiks)->next);
        id++;
        if( !strcmp( (*topiks)->topic_name,top)) return id;

        if ((*topiks)->next == NULL){

            if (!strcmp( (*topiks)->topic_name,top)){

                return id+1;
            }else{

                return -1;

            }


        }



    }
    return id;
}
void add_top(topic_node **topics,char *topname){
    topic_node *topic = (topic_node*) malloc(sizeof(topic_node));
    int id =1;

    topic->topic_name = topname;
    topic->follower_list = NULL;

    topic->next = NULL;


    if (*topics != NULL){

        if((*topics)->next == NULL){
            topic->topic_id = 2;
            (*topics)->next = topic;


        }else{

            while( (*topics)->next != NULL){
                (topics) = &((*topics)->next);
                id++;

            }

            (*topics)->next = topic;

            (topics) = &((*topics)->next);
            (*topics)->topic_id = id+1;
        }
    }else{

        topic->topic_id = 1;
        *topics = topic;

    }

}