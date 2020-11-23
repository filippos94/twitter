/*********************************************************//**
 * @file   twitter.h                                         *
 * @author Nikolaos Batsaras <batsaras@csd.uoc.gr>  	     *
 *                                                    	     *
 * @brief  Header file for the needs of cs-240b project 2018 *
 ************************************************************/

#ifndef __TWITTER_H_
#define __TWITTER_H_


struct user {
    int uid;
    struct follower *followers;
    struct tweet_w *wall_head;
    struct tweet_w *wall_sentinel;
    struct user *next;
};

struct tweet_w {
    int tid;
    int uid;
    struct tweet_w *next;
};

struct follower {
    int uid;
    struct follower *next;
};

struct tagged_tweet {
    int tid;
    int uid;
    int timestamp;
    int time_relevance;
    struct tagged_tweet *next;
    struct tagged_tweet *prev;
};



/* global variable, pointer to the head of the users list */
struct user *usersList=new user;

/* global enum, used to specify the tweets hashtags */
typedef enum {
	sports      = 0,
	politics    = 1,
	economics   = 2,
	music       = 3,
	movies      = 4,
	nature      = 5,
	art         = 6,
	environment = 7,
	technology  = 8,
	weather     = 9
}hashtag;

/* global array, array of lists of tagged tweets */
struct tagged_tweet *Hashtags[10];


#endif /* __TWITTER_H_ */
