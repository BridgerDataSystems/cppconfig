
#include "CCPPConfigJSON.hpp"

#include <boost/filesystem.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>
#include <string>
#include <set>
#include <exception>
#include <iostream>

namespace pt = boost::property_tree;
namespace bf = boost::filesystem;

namespace __N_CPPCONFIG__
{
	#define ASSERTINITILIZED if(!this->m_bInitialized) { this->m_strLastError.assign("FAILED because CCPPConfigJSON is not initialized"); return false; }

	bool CCPPConfigJSON::Initialize(std::string strFilePath, std::string strFileName) noexcept
	{
		if (this->m_bInitialized)
		{
			this->m_strLastError.assign("CCPPConfigJSON::Initialize - FAILED because it is already initialiazed");
			return false;
		}

		if (0 == strFilePath.length())
		{
			this->m_strLastError.assign("CCPPConfigJSON::Initialize - FAILED because strFilePath is empty");
			return false;
		}

		if (0 == strFileName.length())
		{
			this->m_strLastError.assign("CCPPConfigJSON::Initialize - FAILED because strFileName is empty");
			return false;
		}

		this->m_strFilePath.clear();
		if ('\\' == *(strFilePath.end() - 1))
			this->m_strFilePath.assign(strFilePath);
		else
			this->m_strFilePath.assign(strFilePath + '\\');

		this->m_strFileName.clear();
		this->m_strFileName.assign(m_strFilePath + strFileName);

		bf::path _path{ m_strFilePath.c_str() };
		bf::path _file{ m_strFileName.c_str() };

		if (!bf::is_directory(_path))
		{
            // path created - this will happen in first initialization
		    if (!bf::create_directory(_path))
		    {
			    this->m_strLastError.assign("CCPPConfigJSON::Initialize - FAILED because directory is NOT created");
			    return false;
		    }
		}

		if (!bf::is_regular_file(_file))
		{
            // file created - this will happen when new file was created
			bf::ofstream(m_strFileName, std::ios::app | std::ios::out);
		}

		this->m_bInitialized = true;

		return true;
	}

	bool CCPPConfigJSON::UnInitialize() noexcept
	{
        ASSERTINITILIZED

		this->m_bInitialized = false;
        
		return true;
	}

	bool CCPPConfigJSON::Add(std::string key, std::string vlaue) noexcept
	{
		ASSERTINITILIZED

		// Create an empty property tree object.
		pt::ptree tree;

		try
		{
			// Parse the JSON into the property tree.
			pt::read_json(m_strFileName, tree);
		}
		catch (const pt::json_parser::json_parser_error & ex)
		{
			this->m_strLastError.assign(std::string{ "CCPPConfigJSON::Add - EXCEPTION occurred with message: "}.append(ex.message()));
            return false;
		}

		try
		{
			tree.add(key, vlaue);
		}
		catch (const pt::json_parser::json_parser_error & ex)
		{
			this->m_strLastError.assign(std::string{ "CCPPConfigJSON::Add - EXCEPTION occurred with message: "}.append(ex.message()));
            return false;
		}

		try
		{
			// Write property tree to JSON file
			pt::write_json(m_strFileName, tree);
		}
		catch (const pt::json_parser::json_parser_error & ex)
		{
			this->m_strLastError.assign(std::string{ "CCPPConfigJSON::Add - EXCEPTION occurred with message: "}.append(ex.message()));
            return false;
		}

        return true;
	}

	bool CCPPConfigJSON::Add(std::string key, std::vector<std::string> values) noexcept
	{
		ASSERTINITILIZED

		// Create an empty property tree object.
		pt::ptree tree;

		try
		{
			// Parse the JSON into the property tree.
			pt::read_json(m_strFileName, tree);
		}
		catch (const pt::json_parser::json_parser_error & ex)
		{
			this->m_strLastError.assign(std::string{ "CCPPConfigJSON::Add - EXCEPTION occurred with message: "}.append(ex.message()));
            return false;
		}

		try
		{
			// Add all the modules. Unlike put, which overwrites existing nodes, add
			// adds a new node at the lowest level, so the "modules" node will have
			// multiple "module" children.
			BOOST_FOREACH(const std::string & name, values)
				tree.add(key, name);
		}
		catch (const pt::json_parser::json_parser_error & ex)
		{
			this->m_strLastError.assign(std::string{ "CCPPConfigJSON::Add - EXCEPTION occurred with message: "}.append(ex.message()));
            return false;
		}

		try
		{
			// Write property tree to JSON file
			pt::write_json(m_strFileName, tree);
		}
		catch (const pt::json_parser::json_parser_error & ex)
		{
			this->m_strLastError.assign(std::string{ "CCPPConfigJSON::Add - EXCEPTION occurred with message: "}.append(ex.message()));
            return false;
		}

        return true;
	}

	bool CCPPConfigJSON::Load(std::string key, std::string & value) noexcept
	{
		ASSERTINITILIZED

		// Create empty property tree object
		pt::ptree tree;

		try
		{
			// Parse the JSON into the property tree.
			pt::read_json(m_strFileName, tree);
		}
		catch (const pt::json_parser::json_parser_error & ex)
		{
			this->m_strLastError.assign(std::string{ "CCPPConfigJSON::Load - EXCEPTION occurred with message: "}.append(ex.message()));
            return false;
		}

		try
		{
			// If the path cannot be resolved, an exception is thrown.
			value = tree.get<std::string>(key);
		}
		catch (const pt::json_parser::json_parser_error & ex)
		{
			this->m_strLastError.assign(std::string{ "CCPPConfigJSON::Load - EXCEPTION occurred with message: "}.append(ex.message()));
            return false;
		}

		return true;
	}

	bool CCPPConfigJSON::Load(std::string key, std::vector<std::string>& values) noexcept
	{
		ASSERTINITILIZED

		// Create empty property tree object
		pt::ptree tree;

		try
		{
			// Parse the JSON into the property tree.
			pt::read_json(m_strFileName, tree);
		}
		catch (const pt::json_parser::json_parser_error & ex)
		{
			this->m_strLastError.assign(std::string{ "CCPPConfigJSON::Load - EXCEPTION occurred with message: "}.append(ex.message()));
            return false;
		}

		try
		{
			BOOST_FOREACH(pt::ptree::value_type & v, tree.get_child(key))
			{
				// The data function is used to access the data stored in a node.
				values.push_back(v.second.data());
			}
		}
		catch (const pt::json_parser::json_parser_error & ex)
		{
			this->m_strLastError.assign(std::string{ "CCPPConfigJSON::Load - EXCEPTION occurred with message: "}.append(ex.message()));
            return false;
		}

        return true;
	}

	bool CCPPConfigJSON::Delete(const std::string Key) noexcept
	{
		ASSERTINITILIZED

		// Create empty property tree object
		pt::ptree tree;

		try
		{
			// Parse the JSON into the property tree.
			pt::read_json(m_strFileName, tree);
		}
		catch (const pt::json_parser::json_parser_error & ex)
		{
			this->m_strLastError.assign(std::string{ "CCPPConfigJSON::Delete - EXCEPTION occurred with message: "}.append(ex.message()));
            return false;
		}

		try
		{
			// If the path cannot be resolved, an exception is thrown.
			tree.erase(Key);
		}
		catch (const pt::json_parser::json_parser_error & ex)
		{
			this->m_strLastError.assign(std::string{ "CCPPConfigJSON::Delete - EXCEPTION occurred with message: "}.append(ex.message()));
            return false;
		}
        
        return true;
	}

	ICPPConfig* CreateCPPConfigJSON() noexcept
	{
		return new CCPPConfigJSON();
	}    
    
    void DestroyCPPConfigJSON(ICPPConfig** ppObj) noexcept
    {
        if(!ppObj)
            return;

        if(!*ppObj)
            return;

        delete *ppObj;
        *ppObj = nullptr;
    }
} // !__N_CPPCONFIG__