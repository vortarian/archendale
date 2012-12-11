#include <cgi/CGI.h>
#include <exception/Exception.h>
#include <iostream>
#include <vector>
#include <string>
#include <unistd.h>

using namespace std;
using namespace archendale;


void printValues(CGI& cgi)
{
	cout << "Content-type: text/html\n\n" << endl;

	cout << "<HTML>" << endl;
	cout << "<HEAD>" << endl;
	cgi.writeJavascriptData();
	cout << "<script type=\"text/javascript\">" << endl;
	cout << "function _onclick()" << endl
		<< "{ " << endl
		<< "\tvar htmlString = new String();" << endl
		<< "\tfor(var i in CGI)" << endl
		<< "\t{" << endl
		<< "\t\thtmlString +=\"CGI[\" + i + \"] = \" + CGI[i] + \"\\n\";" << endl
		<< "\t} // for" << endl
		<< "\talert(htmlString);" << endl
		<< "} // _onclick" << endl
		<< "</script>" << endl;
	cout << "</HEAD>" << endl << "<BODY>" << endl;
	cout << "<BR><button onclick=\"_onclick()\">View CGIData</button>" << endl;

	cout << "<BR>Environment: <BR>" << endl;
	for(int i = 0; environ[i]; i++)
	{
		cout << "<BR>" << environ[i] << endl;
	} // for

	cout << "<BR>CGI Params: <BR>" << endl;
	cout << "<BR>server_software:" << cgi.getServerSoftware() << endl;
	cout << "<BR>server_name:" << cgi.getServerName() << endl;
	cout << "<BR>gateway_interface:" << cgi.getGatewayInterface() << endl;
	cout << "<BR>server_protocol:" << cgi.getServerProtocol() << endl;
	cout << "<BR>server_port:" << cgi.getServerPort() << endl;
	cout << "<BR>request_method:" << cgi.getRequestMethod() << endl;
	cout << "<BR>path_info:" << cgi.getPathInfo() << endl;
	cout << "<BR>path_translated:" << cgi.getPathTranslated() << endl;
	cout << "<BR>script_name:" << cgi.getScriptName() << endl;
	cout << "<BR>query_string:" << cgi.getQueryString() << endl;
	cout << "<BR>remote_host:" << cgi.getRemoteHost() << endl;
	cout << "<BR>remote_addr:" << cgi.getRemoteAddr() << endl;
	cout << "<BR>auth_type:" << cgi.getAuthType() << endl;
	cout << "<BR>remote_user:" << cgi.getRemoteUser() << endl;
	cout << "<BR>remote_ident:" << cgi.getRemoteIdent() << endl;
	cout << "<BR>content_type:" << cgi.getContentType() << endl;
	cout << "<BR>content_length:" << cgi.getContentLength() << endl;
	cout << "</BODY></HTML>" << endl;
} // printValues

int main(void)
{
	CGI cgi;
	vector<string> queryKeys = cgi.getAllKeys();
	vector<string>::const_iterator start = queryKeys.begin();
	vector<string>::const_iterator end = queryKeys.end();
	try 
	{
		for(;start != end; start++) 
		{
			cgi.setValue(*start, cgi.getValue(*start));
		} // while
	} catch (ObjectNotFoundException exp) 
	{
		cerr << "Caught ObjectNotFoundException: " << exp.why() << endl;
		return -1;
	} // catch
	printValues(cgi);
	return 0;
} // main
