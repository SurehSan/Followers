#include <iostream>
#include <stack>
#include <queue>
#include <fstream>
#include <vector>
#include <map>
#include <cstring>
using namespace std;

class follow {
    public:
        follow(ifstream& gfile); //follow constructor
        void follows(string s); //checks who x follows
        int mutual_followers(); //count of pairs that follow eachother
        int unique_users(ifstream& gfile);//counnt of all unique users.
        void most_followers(); //prints who has most followers and how many
    private:
        vector<string> user_list; //simple vector of users
        map<string, vector<string>> follow_map; //map of users (key) and a vector of people people they follow (values)
        map<string, int> followers; //map of users (key) and the amount of people following them (values)
//follows is considered a member variable
};

follow::follow (ifstream& gfile)
{
//already scanned in the full file

//my approach is to use a map of vectors:
//the key is the follower, the values are the followees.

//a is the follower in string form
//b is the followee in string form

//initate a loop that goes on while there are still lines to print
//my idea is to get the first string into a, the follower.
//Then, the next line ( which will be a : ) will essentially just be a useless variable to scan in the :
//Then, it will initally another while loop that stops when it detects a line that isn't a username.

    string colon = ":";
    string a, b, c;
    while ( gfile >> a )
    {
        gfile >> c;
        gfile >> b;
        //skip the first colon
        //while it does not detect another colonr

        while ( b != ":" )
        {
            if ( follow_map[a].size() < 50 )
            {
                follow_map[a].push_back(b);
            }
            gfile >> b;
        }
    }


// strcpy will probably be a good thing to use.
// separated by :
// if there is a tie in most followers, list them all
// map of vectors is fine

}

//instead of counting the number of special users, count the

void follow::follows(string s)
{
    for (auto &n: follow_map[s])
        cout << n << endl;
}

int follow::unique_users(ifstream& gfile)
{
//cycle through the entire file and add unique users to a vector or array of strings
//checks
//  char a[50];
    string a;
    bool duplicate;

    while ( gfile >> a)
    {
        duplicate = false;
        //for loop to compare to every other known user
        for (auto &u: user_list)
        {
            if (a == u)
                duplicate = true;
        }
        //if we don't find a duplicate, then we add that new user
        if (duplicate == false && a != ":")
            user_list.push_back(a);
    }
    //return count - 1 because one of them are colons
    return user_list.size();
}

int follow::mutual_followers()
{
    //create a nested loop
    //outer loop loops through all of the people F1 who are following someone
    //inner loop checks if each person being followed F2 is following F1
    int count = 0;

    for ( auto &f1: follow_map) //follower
    {
        for (auto &f2: follow_map[f1.first]) //followee
        {
            for (auto &f3: follow_map[f2])
            {
                if (f3 == f1.first)
                    ++count;
            }
        }
    }
    //converts from users to pairs
    return count / 2;
}

void follow::most_followers()
{
    int count;
    for (auto &u: user_list)    //for each user
    {
        count = 0;
        for (auto &f1: follow_map)
        {
            for ( auto &f2: follow_map[f1.first])
            {
                if (f2 == u)
                    count++;
            }
        }
        followers[u] = count;
    }

    string most_famous_user;
    int follower_count = 0;


//check for highest follower count
    for ( auto &p: followers)
    {
        if (p.second > follower_count)
        {
            follower_count = p.second;
            most_famous_user = p.first;
        }
    }

//check for ties
    for (auto &p: followers)
    {
        if (p.second == follower_count)
            cout << "The user with the most followers is " << p.first << " with " << follower_count << " total followers!" << endl;
    }


}


int main(int argc, char *argv[])
{
    ifstream follow_file;
    ifstream new_file;
   //checking to see if file was entered on command line
    if ( argc != 2 )
    {
        cout << "File was not supplied\n";
        return 2;
    }

    follow_file.open( argv[1] );

    // checking to see if file was opened successfully
    if( ! follow_file.is_open() )
    {
        cout << "File could not be opened\n";
        return 3;
    }
    follow f(follow_file);

    new_file.open( argv[1] );

    cout << "Total number of unique users: " << f.unique_users(new_file) << endl;
    cout << "Total number of pairs who follow eachother: " << f.mutual_followers() << endl;

    f.most_followers();



}








