///////////////////////////////////////////////////////////////////////
// DbCore.cpp - Provides test stub for DB prototype                  //
// ver 1.0                                                           //
// Language:    Visual C++ 11                                        //
// Application: CSE687 - Object Oriented Design                      //
// Author:      Anuja Mahajan, Syracuse University(MSCS-Spring 2018) //
//				apmahaja@syr.edu									 //
// Source:      Jim Fawcett, CST 4-187, Syracuse University          //
//              (315) 443-3948, jfawcett@twcny.rr.com                //
///////////////////////////////////////////////////////////////////////

#include "../Utilities/StringUtilities/StringUtilities.h"
#include "../Utilities/TestUtilities/TestUtilities.h"

//----< test stub >----------------------------------------------------
#ifdef TEST_DBCORE

using namespace Utilities;
using namespace NoSqlDb;

int main()
{
	Utilities::Title("Testing DbCore - Database operations");
	DbProvider dbp;
	DbCore<Payload> db = dbp.db();
	// create some demo elements and insert into db
	std::cout << "\n  Adding element in db";
	std::string filepath = "DbCore";
	std::vector<std::string> categories = { "DbCore","Query1","Utility" };
	Payload p(filepath, categories);
	DbElement<Payload> dbElem;
	dbElem.name("J.");
	dbElem.descrip("CSE687");
	dbElem.dateTime(DateTime().now());
	dbElem.payLoad(p);
	db["Fawcett"] = dbElem;
	showHeader();
	showElem("Fawcett", dbElem);
	putLine(2);

	std::string childKey = "ABC";
	DbElement<Payload> dbElement;
	std::string s = "Utility";
	std::vector<std::string> c = { "DbCore","Utilities" };
	Payload p1(s, c);
	dbElement.name("XYZ");
	dbElement.descrip("Internation student..");
	dbElement.payLoad(p1);
	dbElement.dateTime(DateTime().now());
	db[childKey] = dbElement;

	std::cout << "\n  Add children into key \"Sun\" ";
	std::string parentKey = "Sun";
	std::unordered_map<std::string, DbElement<Payload>>& dbStore = db.dbStore();
	std::unordered_map<std::string, DbElement<Payload>>::iterator it = dbStore.find("Fawcett");

	if (it == dbStore.end()) {
		std::cout << "\n  Key " << parentKey << "does not exist in database";
		return false;
	}
	else {
		std::vector<std::string>& children = db["Fawcett"].children();
		std::vector<std::string>::iterator position = std::find(children.begin(), children.end(), childKey);
		if (position == children.end()) {
				children.push_back(childKey);
			std::cout << "\n  Children added in " << "Fawcett";
		}
		else {
			std::cout << "\n  Children " << childKey << " already added in " << "Fawcett";
		}
	}
	showDb(db);
	std::cin.get();
	return 0;
}
#endif
