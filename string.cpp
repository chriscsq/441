/*

GET http://detectportal.firefox.com/success.txt HTTP/1.1
Host: detectportal.firefox.com
User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10.14; rv:62.0) Gecko/20100101 Firefox/62.0
Accept: 
Accept-Language: en-US,en;q=0.5
Accept-Encoding: gzip, deflate
Cache-Control: no-cache
Pragma: no-cache
Connection: keep-alive


Connection: keep-alive
Upgrade-Insecure-Requests: 1

*/

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <string>
#include <regex>


/*

		int stripColon = getCopy.find(":");
		string stripHTTPGET = getCopy.substr(stripColon + 1);
		string newUrl = "http:" + stripHTTPGET;
		newUrl = newUrl.erase(newUrl.find(" "));

		cout << newUrl << endl;
*/

using namespace std;

int main() {

	string getCopy = "GET http://pages.cpsc.ucalgary.ca/~carey/CPSC441/test1.html HTTP/1.1";

	/*
	int pos = s.find(":");
	string subs = s.substr(pos + 1);

	string url = "http:" + subs;

	string urlp = url.erase(url.find(" "));

	cout << "string is: " << urlp << endl;
	*/


	int stripColon = getCopy.find("/");
	string stripHTTPGET = getCopy.substr(stripColon + 2);
	string newUrl = stripHTTPGET;
	newUrl = newUrl.erase(newUrl.find("/"));
	//newUrl = newUrl.push_back();
	char charUrl[1024];
	strcpy(charUrl, newUrl.c_str());

	cout << charUrl << endl;


	return 0;
}


