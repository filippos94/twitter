/*********************************************************//**
 * @file   main.c                                            *
 * @author Nikolaos Batsaras <batsaras@csd.uoc.gr>  	     *
 *                                                    	     *
 * @brief  Source file for the needs of cs-240b project 2018 *
 ************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <iostream>
#include "twitter.h"

#define BUFFER_SIZE 1024  /* Maximum length of a line in input file */

/* Uncomment the following line to enable debugging prints 
 * or comment to disable it */
 #define DEBUG 

#ifdef DEBUG
#define DPRINT(...) fprintf(stderr, __VA_ARGS__);
#else  /* DEBUG */
#define DPRINT(...)
#endif /* DEBUG */

using namespace std;

/**
 * @brief Optional function to initialize data structures that 
 *        need initialization
 *
 * @return 1 on success
 *         0 on failure
 */
struct user *tmp=new user;

int initialize(){	
		usersList->uid=0;
		usersList->next=NULL;	
		usersList->followers=NULL;
		usersList->wall_head=NULL;
		usersList->wall_sentinel=NULL;	
		
		int i=0;
		while(i<=9){
			Hashtags[i]=NULL;
			i++;
	}
		
	return 1;
}

/**
 * @brief Print all active users
 *
 * @return 1 on success
 *         0 on failure
 */
int print_users(void)
{
		struct user *tmp=new user;		
		tmp=usersList;	/*initialize tmp varilable with the head of user list*/	
		struct follower *tmp_follower=new follower;
		struct tweet_w *tmp_tweet=new tweet_w;
		int i=1;
	
	while(tmp!=NULL){	/*print all the users with their follower and the tweets they have*/					
		tmp_follower=tmp->followers;
		tmp_tweet=tmp->wall_head;
		cout<<"\nUser"<<i<<":"<<tmp->uid<<"\n";	
		cout<<"Followers"<<i<<":";
		while(tmp_follower!=NULL){
			cout<<"<"<<tmp_follower->uid<<">,";
			tmp_follower=tmp_follower->next;
		}
			cout<<"\nTweets"<<i<<":";
			while(tmp_tweet!=tmp->wall_sentinel){
				cout<<"<"<<tmp_tweet->tid<<">,";
				tmp_tweet=tmp_tweet->next;
			}
		cout<<"\n";	
		tmp=tmp->next;	
		i++;
	}
	return 1;
}

int print_tweet_list(){
	struct tweet_w *tmp_tweet=new tweet_w;
	struct user *tmp_user=new user;
	int i=1;
	cout<<"\n";											/*Print the tweet list */
	tmp_user=usersList;
	while(tmp_user!=NULL){
		tmp_tweet=tmp_user->wall_head;
		cout<<"User"<<i<<"("<<tmp_user->uid<<")=";
		while(tmp_tweet!=tmp_user->wall_sentinel){
			cout<<"<"<<tmp_tweet->tid<<":"<<tmp_tweet->uid<<">,";
			tmp_tweet=tmp_tweet->next;
		}
		cout<<"\n";
		i++;
		tmp_user=tmp_user->next;
	}	
	return 1;
}



/**
 * @brief Print all tagged tweets
 *
 * @return 1 on success
 *         0 on failure
 */
int print_tweets(void)
{
	struct tagged_tweet *tmp_tagged=new tagged_tweet;
	int i=0;
	cout<<"\n";
	while(i<=9){ /*Print all the Hashtags*/				
		tmp_tagged=Hashtags[i];
			cout<<"Hashtag"<<i<<"= ";
		while(tmp_tagged!=NULL){
			cout<<"<"<<tmp_tagged->tid<<":"<<tmp_tagged->uid<<":"<<tmp_tagged->timestamp<<":"<<tmp_tagged->time_relevance<<">,";
			tmp_tagged=tmp_tagged->next;
		
		}
		cout<<"\n";
		i++;
	}
	return 1;
}

void display(){		/*Function that print the users list*/
	tmp=usersList;
	cout<<"Users=";
	while(tmp!=NULL){
		cout<<"<"<<tmp->uid<<">,";
		tmp=tmp->next;
	}
	cout<<"\n \n";
}


/**
 * @brief Register user
 *
 * @param uid The user's id
 *
 * @return 1 on success
 *         0 on failure
 */
int register_user(int uid)
{
		static int count=0;
		if(count==0){					/* if the head of the node is NULL add the node to the head*/
			usersList->uid=uid;
			count++;
		}
		else{
			struct user *n_User= new user;/*else add the user at the right position*/
			n_User->uid=uid;	
			n_User->next=NULL;
			n_User->wall_head=NULL;
			n_User->followers=NULL;
			n_User->wall_sentinel=NULL;
			
			if(n_User->uid<usersList->uid){
				n_User->next=usersList;
				usersList=n_User;
			}
			else{
				tmp=usersList;
				while((tmp->next!=NULL)&&(tmp->next->uid<n_User->uid)){
					tmp=tmp->next;
				}
				n_User->next=tmp->next;
				tmp->next=n_User;
			}
		}
		display();
		cout<<"\n\n";
	return 1;
}

/**
 * @brief User uid1 is now following user uid2
 *
 * @param uid1 The 1st user's id
 * @param uid2 The 2nd user's id
 *
 * @return 1 on success
 *         0 on failure
 */
int subscribe(int uid1, int uid2)
{
	tmp=usersList;
	struct follower *newFollower=new follower; 
	struct follower *currFollower=new follower;
	
	while(tmp->next!=NULL&&tmp->uid!=uid1){ /*Traverse the list until find the node with uid1*/
		tmp=tmp->next;			
	}
		currFollower=tmp->followers;
		if(tmp->followers==NULL){         /*if the folllowers list is empty*/
			newFollower->uid=uid2;
			newFollower->next=NULL;
			tmp->followers=newFollower;
		}
		else{
			newFollower->uid=uid2;
			newFollower->next=NULL;
		
			if(newFollower->uid<tmp->followers->uid){ /*add the new follower at the right position*/
						newFollower->next=tmp->followers;
						tmp->followers=newFollower;
			}
			else{
				currFollower=tmp->followers;
				while((currFollower->next!=NULL)&&(currFollower->next->uid<newFollower->uid)){
					currFollower=currFollower->next;
				}
			newFollower->next=currFollower->next;
			currFollower->next=newFollower;
		}
}
	
	cout<<"Followers=";
		currFollower=tmp->followers;
		while(currFollower!=NULL){
			cout<<"<"<<currFollower->uid<<">,";
			currFollower=currFollower->next;
		}
	cout<<"\n\n";
	return 1;
}


/**
 * @brief New tweet event
 * 
 * @param uid            The user who posted the tweet
 * @param tid            The tweet's id
 * @param tag            The tweet's hashtag
 * @param timestamp      The time the tweet was posted
 * @param time_relevance How long the tweet was relevant/trending
 *
 * @return 1 on success
 *         0 on failure
 */
int tweet(int uid, int tid, int tag, int timestamp, int time_relevance)
{
	bool temp=true;
	struct user *tmp_user=new user;								/*variable to traverse the users list*/
	struct follower *tmp_follower=new follower; 				/*variable to traverse the follower list*/
	struct tweet_w *tmp_tweet=new tweet_w;     				    /*variable to traverse the tweet_w list*/
	struct tweet_w *sentinel=new tweet_w;
	struct tagged_tweet *new_tagged=new tagged_tweet;	    	/*variable to add a new node to tweet list*/
	struct tagged_tweet *head_tagged=new tagged_tweet;		    /*variable to store the head of the tweets list */
	struct tagged_tweet *tmp_tagged=new tagged_tweet; 			/*variable to traverse the tweet list*/
	tmp_user=usersList;											/*iniatilize the tmp_user with the head of the list*/
	while((tmp_user->uid!=uid)&&(tmp_user!=NULL))				/*find the user position */
	  tmp_user=tmp_user->next;
										/*Insert the uid tweet to his own tweet list if the list is empty */
		
												/*Insert the uid tweet to his own tweet list if the list is empty if the tweet list is not empty*/
			tmp_tweet->uid=uid;
			tmp_tweet->tid=tid;
			tmp_tweet->next=tmp_user->wall_head;
			tmp_user->wall_head=tmp_tweet;
			if(tmp_user->wall_sentinel==NULL){
					sentinel->tid=-1;
					sentinel->uid=-1;
					sentinel->next=NULL;
					tmp_user->wall_sentinel=sentinel;		
					tmp_user->wall_head->next=tmp_user->wall_sentinel;
			}
	tmp_follower=tmp_user->followers;			
	tmp_user=usersList;							/*initialize tmp_user with the head of users list */

	while(tmp_follower!=NULL){					/*traverse the followers list until NULL*/
		while((tmp_user->uid!=tmp_follower->uid)&&(tmp_user!=NULL))
			tmp_user=tmp_user->next;
			
			struct tweet_w *tmp_tweet=new tweet_w; 				
			tmp_tweet->uid=uid;
			tmp_tweet->tid=tid;
			tmp_tweet->next=tmp_user->wall_head;
			tmp_user->wall_head=tmp_tweet;
			if(tmp_user->wall_sentinel==NULL){
					struct tweet_w *sentinel=new tweet_w;
					sentinel->tid=-1;
					sentinel->uid=-1;
					sentinel->next=NULL;
					tmp_user->wall_sentinel=sentinel;
					tmp_user->wall_head->next=tmp_user->wall_sentinel;		
					
			}
		tmp_follower=tmp_follower->next; /* move the pointer to the next node of follower list */
}

print_tweet_list();/*call function to print the tweet list*/


								
	if(Hashtags[tag]==NULL){ 	/*if the hashtag is empty*/
		head_tagged->tid=tid;
		head_tagged->uid=uid;
		head_tagged->timestamp=timestamp;
		head_tagged->time_relevance=time_relevance;
		head_tagged->next=NULL;
		head_tagged->prev=NULL;
		Hashtags[tag]=head_tagged;
	}
	else{							/*find the right position and add the tweet*/
		new_tagged->tid=tid;
		new_tagged->uid=uid;
		new_tagged->next=NULL;
		new_tagged->prev=NULL;
		new_tagged->timestamp=timestamp;
		new_tagged->time_relevance=time_relevance;
		if((new_tagged->timestamp)<=(Hashtags[tag]->timestamp)){
			new_tagged->next=Hashtags[tag];
			new_tagged->next->prev=new_tagged;
			Hashtags[tag]=new_tagged;
			if(Hashtags[tag]->next!=NULL)
				new_tagged->next->prev=new_tagged;
		}
		else{
			tmp_tagged=Hashtags[tag];
			while(tmp_tagged!=NULL){
				
				if((tmp_tagged->timestamp)>(new_tagged->timestamp)){
					tmp_tagged->prev->next=new_tagged;
					new_tagged->prev=tmp_tagged->prev;
					tmp_tagged->prev=new_tagged;
					new_tagged->next=tmp_tagged;
					break;
					
				}
				 if (tmp_tagged->next==NULL&&(tmp_tagged->timestamp)<=(new_tagged->timestamp)){
						tmp_tagged->next=new_tagged;
						new_tagged->prev=tmp_tagged;
						new_tagged->next=NULL;					
					break;
				}
		tmp_tagged=tmp_tagged->next;						
		}
	  }
	}
	print_tweets();
	cout<<"\n\n";
	return 1;
}

/**
 * @brief User uid1 stopped following user uid2
 *
 * @param uid1 The 1st user's id
 * @param uid2 The 2nd user's id
 *
 * @return 1 on success
 *         0 on failure
 */
int unsubscribe(int uid1, int uid2)
{
	struct user *tmp=new user; 
	tmp=usersList;
	while((tmp!=NULL)&&(tmp->uid!=uid1)){
		tmp=tmp->next;
	}
	if(tmp==NULL) /*if the users didnt found*/
		return 0;
	else{
		struct follower *tempFollower=new follower;
		tempFollower=tmp->followers;
	
		if(tmp->followers==NULL)
			return 0;
			
		else if(tmp->followers->uid==uid2){ /*if the user is at the head of folllowers list*/
			tmp->followers=tmp->followers->next;
		}
		else{
			while(tempFollower->next->uid!=uid2&&tempFollower->next!=NULL){
				tempFollower=tempFollower->next;
			}
				if(tempFollower->next==NULL)
					return 0;
				else if(tempFollower->next!=NULL)
					tempFollower->next=tempFollower->next->next;
		}
	}
	
	
	/*delete uid1 twets*/
			tmp=usersList;
			while((tmp!=NULL)&&(tmp->uid!=uid2)){
				tmp=tmp->next;
			}
		struct tweet_w *tmp_tweet=new tweet_w;
		tmp_tweet=tmp->wall_head;
		bool temp=true;
		while(tmp_tweet!=tmp->wall_sentinel){
				temp=true;
			if(tmp->wall_head->uid==uid1){
						tmp->wall_head=tmp->wall_head->next;
						tmp_tweet=tmp->wall_head;
						temp=true;
			}
			else{
				if(tmp_tweet->next!=tmp->wall_sentinel){
					if(tmp_tweet->next->uid==uid1){
						tmp_tweet->next=tmp_tweet->next->next;
						if(tmp_tweet->next==tmp->wall_sentinel)
								break;
						temp=false;		
					}
					else if(temp==true)
						tmp_tweet=tmp_tweet->next;
				}
				else
					break;
			}	
		}
	print_tweet_list(); /*print the tweet list*/
	return 1;
}

/**
 * @brief Delete user account
 * 
 * @param uid The id of the user account to delete
 * 
 * @return 1 on success
 *         0 on failure
 */
int delete_user(int uid)
{
	int i;
	struct user *tmp_user=new user;
	struct user*tmp=new user;
	 tmp_user=usersList;
	 while((tmp_user->uid!=uid)&&(tmp_user!=NULL)){  /*else i traverse the list till i find the node uid*/
				tmp_user=tmp_user->next;
		}
		if(tmp_user==NULL)   /*if the user did not found in user list */
			return 0;
		struct follower *tmp_follower=new follower;	
		tmp_follower=tmp_user->followers;
			while(tmp_follower!=NULL){  /*unsubscribe the uid followers*/
				unsubscribe(uid,tmp_follower->uid);
				tmp_follower=tmp_follower->next;
			}
			
			tmp_user=usersList;
			while(tmp_user!=NULL){    /*traverse the user list and delete from follower list the user who must delete*/  
				struct follower *tmp_follower=new follower;	
				tmp_follower=tmp_user->followers;
				if(tmp_follower!=NULL){
					if(tmp_user->followers->uid==uid){
							tmp_user->followers=tmp_user->followers->next;
							tmp_follower=tmp_user->followers;
					}
					else{
						if(tmp_follower->next!=NULL){ /*if the user found in the last position */
							while(tmp_follower->next->uid!=uid){
								if(tmp_follower->next!=NULL)
									tmp_follower=tmp_follower->next;	
								else
									break;
								}
								tmp_follower->next=tmp_follower->next->next;
							}
					}
				}
			 tmp_user=tmp_user->next; /*move to the next node*/ 
			}
	
		i=0;					/*delete the tweets of deleted user */									
		while(i<=9){
			if(Hashtags[i]!=NULL){
				struct tagged_tweet *tmp_tagged=new tagged_tweet;
				struct tagged_tweet *tmp_pos=new tagged_tweet;
				tmp_tagged=Hashtags[i];	
				while(tmp_tagged!=NULL){
					if(tmp_tagged->uid==uid){
						if(tmp_tagged==Hashtags[i]){
							if(tmp_tagged->next!=NULL){
								Hashtags[i]=tmp_tagged->next;
								Hashtags[i]->prev=NULL;
								tmp_tagged=Hashtags[i];
							}
							else
								Hashtags[i]=NULL;	
						}
						else{
							if(tmp_tagged->next!=NULL){
							tmp_pos=tmp_tagged->next;
							tmp_tagged->prev->next=tmp_tagged->next;
							tmp_tagged->next->prev=tmp_tagged->prev;		
							tmp_tagged=tmp_pos;
							}
							else{
								tmp_tagged->prev->next=NULL;
							}
						}
					}
				  tmp_tagged=tmp_tagged->next;
				}
			}
			i++;
		}
													/*delete user from usersList*/
		tmp_user=usersList;
		if(usersList->uid==uid)
			usersList=usersList->next;
		else{
			while(tmp_user->next!=NULL){
				if(tmp_user->next->uid==uid){
					tmp_user->next=tmp_user->next->next;
					break;
				}
				else 
				tmp_user=tmp_user->next;
			}
		}
		
		
		
print_tweet_list();					/*print tweets list after the delete*/
print_tweets();						/*print hasthag table after the delete*/				
cout<<"\n \n";
	return 1;
}

/**
 * @brief Lookup tweet in user's wall
 * 
 * @param uid The user's id
 * @param tid The tweet's id
 *
 * @return 1 on success
 *         0 on failure
 */
int lookup(int uid, int tid)
{
	struct user *tmp_user=new user;
	struct tweet_w *tmp_tweet=new tweet_w;
	tmp_user=usersList;

	while((tmp_user->uid!=uid)&&(tmp_user!=NULL)){/*traverse the list to find the user*/
		tmp_user=tmp_user->next;
	}
	if(tmp_user==NULL){
		return 0;
	}
	else{	
	tmp_tweet=tmp_user->wall_head;
	while((tmp_tweet->tid!=tid)&&tmp_tweet!=tmp_user->wall_sentinel){/*traverse the tweet list */
		tmp_tweet=tmp_tweet->next;
	}
	}
	
	cout<<"\n \n"<<"Tweet=<"<<tmp_tweet->tid<<":"<<tmp_tweet->uid<<">";
	cout<<"\n \n";
	return 1;
}

/**
 * @brief Combine tweets that have following tags
 * 
 * @param tag1 The first tag
 * @param tag2 The second tag
 *
 * @return 1 on success
 *         0 on failure
 */
int merge(int tag1, int tag2)
{
	struct tagged_tweet *tmp1=new tagged_tweet;
	struct tagged_tweet *tmp2=new tagged_tweet;
	struct tagged_tweet *curr=new tagged_tweet;
	tmp1=Hashtags[tag1];/*initialize tmp1 with the head of hashtag */
	tmp2=Hashtags[tag2];/*initialize tmp2 with the head of hashtag */ 
	cout<<"Merged=";
				if(tmp1!=NULL&&tmp2!=NULL){ 
					if(tmp1->timestamp<=tmp2->timestamp){
						curr=tmp1;
						tmp1=tmp1->next;
						cout<<"<"<<curr->tid<<":"<<curr->uid<<":"<<curr->timestamp<<":"<<curr->time_relevance<<">,";
				}
				else{
					curr=tmp2;
					tmp2=tmp2->next;
					cout<<"<"<<curr->uid<<":"<<curr->tid<<":"<<curr->timestamp<<":"<<curr->time_relevance<<">,";
				}
			}
				while(tmp1!=NULL&&tmp2!=NULL){
					if(tmp1->timestamp<=tmp2->timestamp){
						curr=tmp1;
						tmp1=tmp1->next;
						cout<<"<"<<curr->uid<<":"<<curr->tid<<":"<<curr->timestamp<<":"<<curr->time_relevance<<">,";
					}
					else{
						curr=tmp2;
						tmp2=curr->next;
						cout<<"<"<<curr->uid<<":"<<curr->tid<<":"<<curr->timestamp<<":"<<curr->time_relevance<<">,";
					}
				}
			if(tmp1==NULL){ /*if the tmp1 is null print the rest of tmp2 list*/
				while(tmp2!=NULL){
						cout<<"<"<<tmp2->uid<<":"<<tmp2->tid<<":"<<tmp2->timestamp<<":"<<tmp2->time_relevance<<">,";
						tmp2=tmp2->next;
					}
			}
			if(tmp2==NULL) /*if tmp2 is null print the rest of tmp1 list*/
				while(tmp1!=NULL){
						cout<<"<"<<tmp1->uid<<":"<<tmp1->tid<<":"<<tmp1->timestamp<<":"<<tmp1->time_relevance<<">,";
						tmp1=tmp1->next;
					}
			
			
			tmp1=Hashtags[tag1];/*print the first list*/
			cout<<"\nTweets1= ";				
 			while(tmp1!=NULL){
 				cout<<"<"<<tmp1->uid<<":"<<tmp1->tid<<":"<<tmp1->timestamp<<":"<<tmp1->time_relevance<<">,";
				tmp1=tmp1->next;
		 }
		 tmp2=Hashtags[tag2];/*print the second list*/
		 cout<<"\nTweets2=";
		 	while(tmp2!=NULL){
						cout<<"<"<<tmp2->uid<<":"<<tmp2->tid<<":"<<tmp2->timestamp<<":"<<tmp2->time_relevance<<">,";
						tmp2=tmp2->next;
					}
	cout<<"\n \n";
	return 1;
}

/**
 * @brief Find tweets of the same tag that were trending
 *        at the same time as the current tweet
 *
 * @param tid The tweet's id
 * @param tag The tweet's hashtag
 *
 * @return 1 on success
 *         0 on failure
 */
int time_relevant(int tid, int tag)
{
	int min_distance;
	int max_distance;
	struct tagged_tweet *tmp_tagged=new tagged_tweet;
	struct tagged_tweet *tmp_back=new tagged_tweet;
	struct tagged_tweet *tmp_forw=new tagged_tweet;
	tmp_tagged=Hashtags[tag];
	while(tmp_tagged->tid!=tid&&tmp_tagged!=NULL)
		tmp_tagged=tmp_tagged->next;             /*traverse till find the node position*/
	if(tmp_tagged!=NULL){
			min_distance=(tmp_tagged->timestamp)-(tmp_tagged->time_relevance);
			max_distance=(tmp_tagged->timestamp)+(tmp_tagged->time_relevance);
			tmp_back=tmp_tagged->prev;
			tmp_forw=tmp_tagged->next;
	}
	else{ /*if the tmp_tagged is NULL the input is incorrect*/
		cout<<"The given tid:"<<tid<<"didn't found in the hashtag:"<<tag;
		return 0;
	}
	cout<<"Relevant Tweets=<"<<tmp_tagged->tid<<":"<<tmp_tagged->uid<<":"<<tmp_tagged->timestamp<<":"<<tmp_tagged->time_relevance<<">,";
	
	if(tmp_back==NULL){
		while(tmp_forw->timestamp<=max_distance&&tmp_forw!=NULL){
					cout<<"<"<<tmp_forw->tid<<":"<<tmp_forw->uid<<":"<<tmp_forw->timestamp<<":"<<tmp_forw->time_relevance<<">,";		
					tmp_forw=tmp_forw->next;
		}
	}
	
	else if(tmp_forw==NULL){
			while(tmp_back->timestamp>=min_distance&&tmp_back!=NULL){
						cout<<"<"<<tmp_back->tid<<":"<<tmp_back->uid<<":"<<tmp_back->timestamp<<":"<<tmp_back->time_relevance<<">,";
						tmp_back=tmp_back->prev;
			}
	}
	else{	
		while((tmp_back!=NULL&&tmp_back->timestamp>=min_distance)||(tmp_forw!=NULL&&tmp_forw->timestamp<=max_distance)){
				if((tmp_back!=NULL)&&(tmp_back->timestamp>=min_distance)){
					cout<<"<"<<tmp_back->tid<<":"<<tmp_back->uid<<":"<<tmp_back->timestamp<<":"<<tmp_back->time_relevance<<">,";
					tmp_back=tmp_back->prev;
				}
				if(tmp_forw!=NULL&&tmp_forw->timestamp<=max_distance){
					cout<<"<"<<tmp_forw->tid<<":"<<tmp_forw->uid<<":"<<tmp_forw->timestamp<<":"<<tmp_forw->time_relevance<<">,";		
					tmp_forw=tmp_forw->next;
				}
		}
	}
	
	
	cout<<"\n \n";	
	return 1;
}




/**
 * @brief Free resources
 *
 * @return 1 on success
 *         0 on failure
 */
int free_all(void)
{
	return 1;
}


/**
 * @brief The main function
 *
 * @param argc Number of arguments
 * @param argv Argument vector
 *
 * @return 0 on success
 *         1 on failure
 */
int main(int argc, char** argv)
{
	FILE *fin = NULL;
	char buff[BUFFER_SIZE], event;

	/* Check command buff arguments */
	if (argc != 2) {
		fprintf(stderr, "Usage: %s <input_file> \n", argv[0]);
		return EXIT_FAILURE;
	}

	/* Open input file */
	if (( fin = fopen(argv[1], "r") ) == NULL ) {
		fprintf(stderr, "\n Could not open file: %s\n", argv[1]);
		perror("Opening test file\n");
		return EXIT_FAILURE;
	}

	/* Initializations */
	initialize();

	/* Read input file buff-by-buff and handle the events */
	while (fgets(buff, BUFFER_SIZE, fin)) {

		DPRINT("\n>>> Event: %s", buff);

		switch(buff[0]) {

			/* Comment */
			case '#':
				break;

			/* Register user
			 * R <uid> */
			case 'R':
				{
					int uid;

					sscanf(buff, "%c %d", &event, &uid);
					DPRINT("%c %d\n", event, uid);

					if (register_user(uid)) {
						DPRINT("R %d succeeded\n", uid);
					} else {
						fprintf(stderr, "R %d failed\n", uid);
					}

					break;
				}

			/* User uid1 is now following user uid2
			 * S <uid1> <uid2> */
			case 'S':
				{
					int uid1, uid2;

					sscanf(buff, "%c %d %d", &event, &uid1, &uid2);
					DPRINT("%c %d %d\n", event, uid1, uid2);

					if (subscribe(uid1, uid2)) {
						DPRINT("%c %d %d succeeded\n", event, uid1, uid2);
					} else {
						fprintf(stderr, "%c %d %d failed\n", event, uid1, uid2);
					}

					break;
				}

			/* New tweet event
			 * T <uid> <tid> <hashtag> <timestamp> <time_relevance> */
			case 'T':
				{
					int uid, tid, tag, timestamp, time_relevance;

					sscanf(buff, "%c %d %d %d %d %d", &event, &uid, &tid, &tag, &timestamp, &time_relevance);
					DPRINT("%c %d %d %d %d %d", event, uid, tid, tag, timestamp, time_relevance);

					if (tweet(uid, tid, tag, timestamp, time_relevance)) {
						DPRINT("%c %d %d %d %d %d succeeded\n", event, uid, tid, tag, timestamp, time_relevance);
					} else {
						fprintf(stderr, "%c %d %d %d %d %d failed\n", event, uid, tid, tag, timestamp, time_relevance);
					}

					break;
				}

			/* User uid1 stopped following user uid2
			 * U <uid1> <uid2> */
			case 'U':
				{
					int uid1, uid2;

					sscanf(buff, "%c %d %d", &event, &uid1, &uid2);
					DPRINT("%c %d %d\n", event, uid1, uid2);

					if (unsubscribe(uid1, uid2)) {
						DPRINT("%c %d %d succeeded\n", event, uid1, uid2);
					} else {
						fprintf(stderr, "%c %d %d failed\n", event, uid1, uid2);
					}

					break;
				}

			/* Delete user account
			 * D <uid> */
			case 'D':
				{
					int uid;

					sscanf(buff, "%c %d", &event, &uid);
					DPRINT("%c %d\n", event, uid);

					if (delete_user(uid)) {
						DPRINT("%c %d succeeded\n", event, uid);
					} else {
						fprintf(stderr, "%c %d failed\n", event, uid);
					}

					break;
				}

			/* Lookup tweet in user's wall
			 * L <uid> <tid> */
			case 'L':
				{
					int uid, tid;

					sscanf(buff, "%c %d %d\n", &event, &uid, &tid);
					DPRINT("%c %d %d\n", event, uid, tid);

					if (lookup(uid, tid)) {
						DPRINT("%c %d %d succeeded\n", event, uid, tid);
					} else {
						fprintf(stderr, "%c %d %d failed\n", event, uid, tid);
					}

					break;
				}

			/* Combine tweets that have following tags
			 * M <hashtag1> <hashtag2> */
			case 'M':
				{
					int tag1, tag2;

					sscanf(buff, "%c %d %d", &event, &tag1, &tag2);
					DPRINT("%c %d %d\n", event, tag1, tag2);

					if (merge(tag1, tag2)) {
						DPRINT("%c %d %d succeeded\n", event, tag1, tag2);
					} else {
						fprintf(stderr, "%c %d %d failed\n", event, tag1, tag2);
					}

					break;
				}

			/* Find tweets of the same tag that were trending
			 * at the same time as the current tweet
			 * F <tid> <hashtag> */
			case 'F':
				{
					int tid, tag;

					sscanf(buff, "%c %d %d", &event, &tid, &tag);
					DPRINT("%c %d %d\n", event, tid, tag);

					if (time_relevant(tid, tag)) {
						DPRINT("%c %d %d succeeded\n", event, tid, tag);
					} else {
						fprintf(stderr, "%c %d %d failed\n", event, tid, tag);
					}

					break;
				}

			/* Print all active users
			 * X */
			case 'X':
				{
					sscanf(buff, "%c", &event);
					DPRINT("%c\n", event);

					if (print_users()) {
						DPRINT("%c succeeded\n", event);
					} else {
						fprintf(stderr, "%c failed\n", event);
					}

					break;
				}

			/* Print all tagged tweets
			 * Y */
			case 'Y':
				{
					sscanf(buff, "%c", &event);
					DPRINT("%c\n", event);

					if (print_tweets()) {
						DPRINT("%c succeeded\n", event);
					} else {
						fprintf(stderr, "%c failed\n", event);
					}

					break;
				}

			/* Empty line */
			case '\n':
				break;

			/* Ignore everything else */
			default:
				DPRINT("Ignoring buff: %s \n", buff);

				break;
		}
	}

	free_all();
	return (EXIT_SUCCESS);
}
