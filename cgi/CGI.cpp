
#include <stdlib.h> // getenv
#include <string>
#include <map>
#include <iostream>

#include <cgi/CGI.h>
#include <exception/Exception.h>

using std::ostream;
using std::cout;
using std::endl;
using std::string;
using std::map;
using std::cerr;

namespace archendale {
	CGI::CGI()
	{
		char* cptr = 0;

		cptr = 0;
		cptr = getenv("SERVER_SOFTWARE");
		if(0 != cptr) m_server_software = cptr;

		cptr = 0;
		cptr = getenv("SERVER_NAME");
		if(0 != cptr) m_server_name = cptr;

		cptr = 0;
		cptr = getenv("GATEWAY_INTERFACE");
		if(0 != cptr) m_gateway_interface = cptr;

		cptr = 0;
		cptr = getenv("SERVER_PROTOCOL");
		if(0 != cptr) m_server_protocol = cptr;

		cptr = 0;
		cptr = getenv("SERVER_PORT");
		if(0 != cptr) m_server_port = cptr;

		cptr = 0;
		cptr = getenv("REQUEST_METHOD");
		if(0 != cptr) m_request_method = cptr;

		cptr = 0;
		cptr = getenv("PATH_INFO");
		if(0 != cptr) m_path_info = cptr;

		cptr = 0;
		cptr = getenv("PATH_TRANSLATED");
		if(0 != cptr) m_path_translated = cptr;

		cptr = 0;
		cptr = getenv("SCRIPT_NAME");
		if(0 != cptr) m_script_name = cptr;

		cptr = 0;
		cptr = getenv("QUERY_STRING");
		if(0 != cptr) m_query_string = cptr;

		cptr = 0;
		cptr = getenv("REMOTE_HOST");
		if(0 != cptr) m_remote_host = cptr;

		cptr = 0;
		cptr = getenv("REMOTE_ADDR");
		if(0 != cptr) m_remote_addr = cptr;

		cptr = 0;
		cptr = getenv("AUTH_TYPE");
		if(0 != cptr) m_auth_type = cptr;

		cptr = 0;
		cptr = getenv("REMOTE_USER");
		if(0 != cptr) m_remote_user = cptr;

		cptr = 0;
		cptr = getenv("REMOTE_IDENT");
		if(0 != cptr) m_remote_ident = cptr;

		cptr = 0;
		cptr = getenv("CONTENT_TYPE");
		if(0 != cptr) m_content_type = cptr;

		cptr = 0;
		cptr = getenv("CONTENT_LENGTH");
		if(0 != cptr) m_content_length = cptr;
		
		string key, value;
		string tempQuery = m_query_string;
		try 
		{
			while(tempQuery.size() > 0)
			{
				key = extractToken(tempQuery);
				value = extractToken(tempQuery);
				m_requestData[key] = value;
			} // while
		} catch(InvalidDataException& exp) 
		{
			cout << "alert(\"Error: " + exp.why() + "\nQuery String: " + tempQuery + ");\"" << endl;
		} // try
	} // CGI

	CGI::CGI(const CGI& rhs)
	{
		m_server_software = rhs.m_server_software;
		m_server_name = rhs.m_server_name;
		m_gateway_interface = rhs.m_gateway_interface;
		m_server_protocol = rhs.m_server_protocol;
		m_server_port = rhs.m_server_port;
		m_request_method = rhs.m_request_method;
		m_path_info = rhs.m_path_info;
		m_path_translated = rhs.m_path_translated;
		m_script_name = rhs.m_script_name;
		m_query_string = rhs.m_query_string;
		m_remote_host = rhs.m_remote_host;
		m_remote_addr = rhs.m_remote_addr;
		m_auth_type = rhs.m_auth_type;
		m_remote_user = rhs.m_remote_user;
		m_remote_ident = rhs.m_remote_ident;
		m_content_type = rhs.m_content_type;
		m_content_length = rhs.m_content_length;
		
		m_requestData = rhs.m_requestData;
		m_responseData = rhs.m_responseData;
	} // CGI

	const CGI& CGI::operator=(const CGI& rhs)
	{
		m_server_software = rhs.m_server_software;
		m_server_name = rhs.m_server_name;
		m_gateway_interface = rhs.m_gateway_interface;
		m_server_protocol = rhs.m_server_protocol;
		m_server_port = rhs.m_server_port;
		m_request_method = rhs.m_request_method;
		m_path_info = rhs.m_path_info;
		m_path_translated = rhs.m_path_translated;
		m_script_name = rhs.m_script_name;
		m_query_string = rhs.m_query_string;
		m_remote_host = rhs.m_remote_host;
		m_remote_addr = rhs.m_remote_addr;
		m_auth_type = rhs.m_auth_type;
		m_remote_user = rhs.m_remote_user;
		m_remote_ident = rhs.m_remote_ident;
		m_content_type = rhs.m_content_type;
		m_content_length = rhs.m_content_length;
		
		m_requestData = rhs.m_requestData;
		m_responseData = rhs.m_responseData;
	} // operator=

	string CGI::getValue(string key)
	{
		map<string, string>::iterator element = m_requestData.find(key);
		if(m_requestData.end() == element)
		{
			ObjectNotFoundException exp(key);
			throw exp;
		} // if
		return element->second;
	} // getValue 

	void CGI::setValue(string key, string value)
	{
		m_responseData[key] = value;
	} // setValue

	void CGI::writeJavascriptData(ostream& ostr) const
	{
		map<string, string>::const_iterator data = m_responseData.begin();
		ostr << "<script type=\"text/javascript\">" << endl;
		ostr << "// CGI Javascript - Archendale.com" << endl;
		ostr << "var CGI = { " << endl;
		while(m_responseData.end() != data)
		{
			ostr << "\t \"" 
				<< data->first
				<< "\": \"" 
				<< data->second
				<< "\"," 
				<< endl;
			data++;
		} // while
		ostr << "}; // CGI Javascript - Archendale.com" << endl << endl;
		ostr << "</script>" << endl;
	} // writeJavascriptData

	string CGI::getServerSoftware() const
	{
		return m_server_software;
	} // getServerSoftware;

	string CGI::getServerName() const
	{
		return m_server_name;
	} // getServerName;

	string CGI::getGatewayInterface() const
	{
		return m_gateway_interface;
	} // getGatewayInterface;

	string CGI::getServerProtocol() const
	{
		return m_server_protocol;
	} // getServerProtocol;

	string CGI::getServerPort() const
	{
		return m_server_port;
	} // getServerPort;

	string CGI::getRequestMethod() const
	{
		return m_request_method;
	} // getRequestMethod;

	string CGI::getPathInfo() const
	{
		return m_path_info;
	} // getPathInfo;

	string CGI::getPathTranslated() const
	{
		return m_path_translated;
	} // getPathTranslated;

	string CGI::getScriptName() const
	{
		return m_script_name;
	} // getScriptName;

	string CGI::getQueryString() const
	{
		return m_query_string;
	} // getQueryString;

	string CGI::getRemoteHost() const
	{
		return m_remote_host;
	} // getRemoteHost;

	string CGI::getRemoteAddr() const
	{
		return m_remote_addr;
	} // getRemoteAddr;

	string CGI::getAuthType() const
	{
		return m_auth_type;
	} // getAuthType;

	string CGI::getRemoteUser() const
	{
		return m_remote_user;
	} // getRemoteUser;

	string CGI::getRemoteIdent() const
	{
		return m_remote_ident;
	} // getRemoteIdent;

	string CGI::getContentType() const
	{
		return m_content_type;
	} // getContentType;

	string CGI::getContentLength() const
	{
		return m_content_length;
	} // getContentLength;

	vector<string> CGI::getAllKeys() const
	{
		vector<string> returnValue;
		map< string, string >::const_iterator mapIterator = m_requestData.begin();
		map< string, string >::const_iterator endMapIterator = m_requestData.end();
		while(mapIterator != endMapIterator)
		{
			returnValue.push_back(mapIterator->first);
			mapIterator++;
		} // while
		return returnValue;
	} // getAllKeys

	string CGI::extractToken(string& queryString)
	{
		// Parsing and breaking down the arguments to the request
		// Each ? represents a new argument
		//	Arguments should be of the for <key><value><key><value> . . . .
		//	e.g. If you have a key of "Glenn", and a value of "Meuth"
		//		then:
		//			?Glenn?Meuth
		// Escape Characters:
		//	\? = ?
		//	\\ = \
		//
		
		string value;
		string::iterator currentPosition = queryString.begin();
		string::iterator endPosition = queryString.end();

		// Advance Past empty arguments by eating empty delimiters
		// If we are not positive the first element is not a '?', then the loop after this
		// one MUST be altered
		while(!(currentPosition == endPosition || *currentPosition != '?')) 
		{
			queryString.erase(currentPosition, currentPosition + 1);
			currentPosition = queryString.begin();
			endPosition = queryString.end();
		} // while
		while(currentPosition != endPosition) 
		{
			switch(*currentPosition)
			{
				case '\\':
					if(
						((currentPosition + 1) < endPosition ) &&
						(
							*(currentPosition + 1) == '?' ||
							*(currentPosition + 1) == '\\'
						)
					)
					{ 
						// skip character, start after next one
						currentPosition++;
					} else 
					{
						InvalidDataException exp("Invalid Escape Sequence, \\ without trailing character");
						throw exp;
					} // if 
					break;
				case '?':
					queryString = string(currentPosition, queryString.end());
					return value;
			} // switch
			value += *currentPosition;
			currentPosition++;
		} // while
		
		// The last arguement will not be followed by a delimiter, so it will be extracted accordingly
		queryString = string(currentPosition, queryString.end());
		return value;
	} // extractToken

} // archendale
