#ifndef CGI_h
#define CGI_h

#include <iostream>
#include <string>
#include <vector>
#include <map>

using std::ostream;
using std::cout;
using std::string;
using std::map;
using std::vector;

namespace archendale {

	class CGI
	{
	public:
		CGI();
		CGI(const CGI&);
		const CGI& operator=(const CGI&);

		string getValue(string);
		void setValue(string, string);

		string getServerSoftware() const;
		string getServerName() const;
		string getGatewayInterface() const;
		string getServerProtocol() const;
		string getServerPort() const;
		string getRequestMethod() const;
		string getPathInfo() const;
		string getPathTranslated() const;
		string getScriptName() const;
		string getQueryString() const;
		string getRemoteHost() const;
		string getRemoteAddr() const;
		string getAuthType() const;
		string getRemoteUser() const;
		string getRemoteIdent() const;
		string getContentType() const;
		string getContentLength() const;
		
		// Returns a vector of strings which contains all key values
		vector<string> getAllKeys() const;
		
		void writeJavascriptData(ostream& = cout) const;
	private:
		string extractToken(string& queryString);
		map<string, string> m_requestData;
		map<string, string> m_responseData;

		// The name and version of the information 
		// server software answering the request 
		// (and running the gateway). Format: name/version

		string m_server_software;
	
		// The server's hostname, DNS alias, or IP 
		// address as it would appear in self-referencing URLs.

		string m_server_name;

		// The revision of the CGI specification to which 
		// this server complies. Format: CGI/revision

		string m_gateway_interface;

		// The name and revision of the information protcol
		//  this request came in with. Format: protocol/revision
		string m_server_protocol;

		// The port number to which the request was sent.
		string m_server_port;

		// The method with which the request was made. For
		//  HTTP, this is "GET", "HEAD", "POST", etc.
		string m_request_method;

		// The extra path information, as given by the client.
		//  In other words, scripts can be accessed by their
		//  virtual pathname, followed by extra information
		//  at the end of this path. The extra information is
		//  sent as PATH_INFO. This information should be
		//  decoded by the server if it comes from a URL before
		//  it is passed to the CGI script.
		string m_path_info;

		// The server provides a translated version of PATH_INFO,
		//  which takes the path and does any virtual-to-physical mapping to it.
		string m_path_translated;

		// A virtual path to the script being executed, used
		//  for self-referencing URLs.
		string m_script_name;

		// The information which follows the ? in the URL 
		// which referenced this script. This is the query
		//  information. It should not be decoded in any 
		// fashion. This variable should always be set when
		//  there is query information, regardless of command
		//  line decoding.
		string m_query_string;

		// The hostname making the request. If the server 
		// does not have this information, it should set
		//  REMOTE_ADDR and leave this unset.
		string m_remote_host;

		// The IP address of the remote host making the request.
		string m_remote_addr;

		// If the server supports user authentication, and
		//  the script is protects, this is the protocol-specific
		//  authentication method used to validate the user.
		string m_auth_type;

		// If the server supports user authentication, and the
		//  script is protected, this is the username they have
		//  authenticated as.
		string m_remote_user;

		// If the HTTP server supports RFC 931 identification,
		//  then this variable will be set to the remote user
		//  name retrieved from the server. Usage of this variable
		//  should be limited to logging only.
		string m_remote_ident;

		// For queries which have attached information, such
		//  as HTTP POST and PUT, this is the content type of
		//  the data.
		string m_content_type;

		// The length of the said content as given by the client.
		string m_content_length;
	}; // CGI

} // archendale

#endif // CGI_h
