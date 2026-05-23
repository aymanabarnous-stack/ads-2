/*************************************************
* ADS Praktikum 2
* Unit-Testdatei
* Stand: 20.05.2024
*
*************************************************
* Änderungen untersagt!
*************************************************/
#include <vector>
#include "catch.h"
#include "MyHashTable.h"


std::vector<Account> accs{
    {"Andi","Passwort","Goole.com"},
    {"Bernt", "testwort","Micromoft.com"},
    {"Sophia", "gutesPassW0rt", "Iterra.com"},
    {"Lukas", "Luk@2024!", "Streamix.com"},
    {"Mia", "MiaSecure77", "Shopora.net"},
    {"Jonas", "J0nas#Safe", "Cloudify.io"},
    {"Emma", "Emm@Love12", "PicShare.org"},
    {"Noah", "Noah_pw_88", "GameHub.gg"},
    {"Lea", "Lea!Pass99", "FitTrack.de"},
    {"Finn", "F1nnSecure!", "Travelio.com"}
};

TEST_CASE("HashTable", "[HASHTABLE]") {

    SECTION("Hashing 10 elements - Size: 20 : Rehashing") {

        MyHashTable h(20,1);
        for (unsigned int i = 0; i < accs.size(); i++)
        {
            h.insert(accs.at(i));
        }
        h.insert({ "Paul", "P@ulSecure21", "CodeBase.dev" });
        h.insert({ "Laura", "L4ura!Pass", "DesignPro.io" });
        h.insert({ "Tim", "Tim_2025#", "DataFlow.net" });
        REQUIRE(h.getCollisionCount() == 9);
        h.insert({ "Nina", "Nina$Strong88", "HealthPlus.app" });
        if (h.getSize() > 40) {
            REQUIRE(h.at(0).acc.username == "Jonas");
            REQUIRE(h.at(3).acc.username == "Nina");
            REQUIRE(h.at(9).acc.username == "Paul");
            REQUIRE(h.at(10).acc.username == "Tim");
            REQUIRE(h.at(11).acc.username == "Emma");
            REQUIRE(h.at(12).acc.username == "Andi");
            REQUIRE(h.at(13).acc.username == "Finn");
            REQUIRE(h.at(15).acc.username == "Bernt");
            REQUIRE(h.at(23).acc.username == "Lukas");
            REQUIRE(h.at(27).acc.username == "Mia");
            REQUIRE(h.at(31).acc.username == "Lea");
            REQUIRE(h.at(34).acc.username == "Laura");
            REQUIRE(h.at(36).acc.username == "Sophia");
            REQUIRE(h.at(40).acc.username == "Noah");
        }
        REQUIRE(h.getSize() == 41);
        REQUIRE(h.getCollisionCount() == 2);
        REQUIRE(h.getNumElements() == 14);

    }
    
    SECTION("Hashing 10 elements - quadratisch Sondieren - Size: 15 : Rehashing") {

        MyHashTable h(15, 2);

        for (unsigned int i = 0; i < accs.size(); i++)
        {
            h.insert(accs.at(i));
        }
        h.insert({ "Paul", "P@ulSecure21", "CodeBase.dev" });
        h.insert({ "Laura", "L4ura!Pass", "DesignPro.io" });
        h.insert({ "Tim", "Tim_2025#", "DataFlow.net" });
        h.insert({ "Nina", "Nina$Strong88", "HealthPlus.app" });

        if (h.getSize() > 26) {
            REQUIRE(h.at(0).acc.username == "Bernt");
            REQUIRE(h.at(1).acc.username == "Laura");
            REQUIRE(h.at(3).acc.username == "Lukas");
            REQUIRE(h.at(9).acc.username == "Nina");
            REQUIRE(h.at(11).acc.username == "Noah");
            REQUIRE(h.at(16).acc.username == "Lea");
            REQUIRE(h.at(18).acc.username == "Finn");
            REQUIRE(h.at(19).acc.username == "Sophia");
            REQUIRE(h.at(20).acc.username == "Mia");
            REQUIRE(h.at(22).acc.username == "Paul");
            REQUIRE(h.at(23).acc.username == "Emma");
            REQUIRE(h.at(24).acc.username == "Jonas");
            REQUIRE(h.at(25).acc.username == "Andi");
            REQUIRE(h.at(26).acc.username == "Tim");
        }
        REQUIRE(h.getSize() == 31);
        REQUIRE(h.getCollisionCount() == 8);
        REQUIRE(h.getNumElements() == 14);
    }

    SECTION("Hashing 10 elements - doppeltes Hashing- Size: 15 : Rehashing") {

        MyHashTable h(15, 3);

        for (unsigned int i = 0; i < accs.size(); i++)
        {
            h.insert(accs.at(i));
        }
        h.insert({ "Paul", "P@ulSecure21", "CodeBase.dev" });
        h.insert({ "Laura", "L4ura!Pass", "DesignPro.io" });
        h.insert({ "Tim", "Tim_2025#", "DataFlow.net" });
        h.insert({ "Nina", "Nina$Strong88", "HealthPlus.app" });

        if (h.getSize() > 29) {
            REQUIRE(h.at(0).acc.username == "Bernt");
            REQUIRE(h.at(2).acc.username == "Tim");
            REQUIRE(h.at(3).acc.username == "Lukas");
            REQUIRE(h.at(7).acc.username == "Nina");
            REQUIRE(h.at(9).acc.username == "Paul");
            REQUIRE(h.at(11).acc.username == "Noah");
            REQUIRE(h.at(16).acc.username == "Lea");
            REQUIRE(h.at(18).acc.username == "Finn");
            REQUIRE(h.at(19).acc.username == "Emma");
            REQUIRE(h.at(20).acc.username == "Mia");
            REQUIRE(h.at(23).acc.username == "Jonas");
            REQUIRE(h.at(25).acc.username == "Andi");
            REQUIRE(h.at(27).acc.username == "Laura");
            REQUIRE(h.at(29).acc.username == "Sophia");
        }
        REQUIRE(h.getSize() == 31);
        REQUIRE(h.getCollisionCount() == 10);
        REQUIRE(h.getNumElements() == 14);
    }
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++