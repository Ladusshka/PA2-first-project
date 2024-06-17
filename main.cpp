#ifndef __PROGTEST__
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <cmath>
#include <cassert>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <functional>
#include <memory>
#endif /* __PROGTEST__ */
struct place{
    std::string city;
    std::string addr;
    std::string region;
    unsigned int id;
    std::string owner;

    place():city(""),addr(""),region(""), id(0),owner(""){}

    place( const std::string    & city,
           const std::string    & addr,
           const std::string    & region,
           unsigned int           id ,
           const std::string & owner):city(city), addr(addr),region(region),id(id),owner(owner){}
};
class CIterator
{
public:
    bool                     atEnd                         () const;
    void                     next                          ();
    std::string              city                          () const;
    std::string              addr                          () const;
    std::string              region                        () const;
    unsigned                 id                            () const;
    std::string              owner                         () const;
    unsigned int return_index() const{
        return index;
    }
    CIterator(const std::vector<place> & rregister, unsigned int startindex ):runner(rregister),index(startindex) {
        size = rregister.size();
        index =0;
    }
    CIterator(){
        size = 0;
        index =0;
    }



private:
    const std::vector<place>  runner;
    unsigned int index, size;
};


bool CIterator::atEnd() const {
    if(runner.empty()){
        return true;
    }
    if ( index >= size )
        return true;
    return false;

}
void CIterator::next(){
    if(!atEnd()){
        index++;
    }else{
        return;
    }

}

std::string CIterator::city() const {
    if(index < runner.size() && !runner.empty())
        return runner[index].city;
    else{
        return "";
    }
}
std::string CIterator::addr() const{
    if(index < runner.size()&& !runner.empty())
        return runner[index].addr;
    else{
        return "";
    }
}
std::string CIterator::region() const {
    if(index < runner.size()&& !runner.empty())
        return runner[index].region;
    else{
        return "";
    }
}
std::string CIterator::owner() const {
    if(index < runner.size()&& !runner.empty())
        return runner[index].owner;
    else{
        return "";
    }
}
unsigned int CIterator::id() const {
    if(index < runner.size()&& !runner.empty())
        return runner[index].id;
    else{
        return 0;
    }
}
class CLandRegister
{
public:
    bool                     add                           ( const std::string    & city,
                                                             const std::string    & addr,
                                                             const std::string    & region,
                                                             unsigned int           id );

    bool                     del                           ( const std::string    & city,
                                                             const std::string    & addr );

    bool                     del                           ( const std::string    & region,
                                                             unsigned int           id );

    bool                     getOwner                      ( const std::string    & city,
                                                             const std::string    & addr,
                                                             std::string          & owner ) const;

    bool                     getOwner                      ( const std::string    & region,
                                                             unsigned int           id,
                                                             std::string          & owner ) const;

    bool                     newOwner                      ( const std::string    & city,
                                                             const std::string    & addr,
                                                             const std::string    & owner );

    bool                     newOwner                      ( const std::string    & region,
                                                             unsigned int           id,
                                                             const std::string    & owner );

    size_t                   count                         ( const std::string    & owner ) const;

    CIterator                listByAddr                    () const;

    CIterator                listByOwner                   ( const std::string    & owner ) const;



private:
    std::vector<place> CityAddr;
    std::vector<place> RegionId;
    std::vector<std::vector<place>> Owners;
};
CIterator CLandRegister::listByAddr() const {

    if(CityAddr.empty()){
        std::vector<place> a;
        CIterator aa(a,0);
        return aa;
    }
    CIterator popa(CityAddr, 0);
    return popa;
}
bool compare_City(const place & a, const place & b){


    if(a.city<b.city){
        return true;
    }
    else if(a.city==b.city){
        return a.addr<b.addr;
    }
    else{
        return false;
    }
}
bool Compare_region(const place & a, const place & b){
    if(a.region < b.region){
        return true;
    }else if(a.region == b.region){
        return a.id<b.id;
    }
    else{
        return false;
    }

}

bool CLandRegister::add(const std::string &city, const std::string &addr, const std::string &region, unsigned int id) {

    place tmp(city, addr,region,id,"");


    auto it = std::lower_bound(CityAddr.begin(), CityAddr.end(),tmp, compare_City);


    if(it!=CityAddr.end()  ){
        if((it->city == city && it->addr == addr) || (it->region == region && it->id==id)){
            return false;
        }
    }

    CityAddr.insert(it,tmp);


    auto it_region = std::lower_bound(RegionId.begin(), RegionId.end(), tmp, Compare_region);

    if(it_region!=RegionId.end()){
        if((it_region->city == city && it_region->addr == addr) || (it_region->region == region && it_region->id==id)){
            it = std::lower_bound(CityAddr.begin(), CityAddr.end(),tmp, compare_City);
            CityAddr.erase(it);
            return false;
        }

    }

    RegionId.insert(it_region,tmp);


    if(Owners.empty()){
        std::vector<place> c;
        c.push_back(tmp);
        Owners.push_back(c);
    }else{
        Owners[0].push_back(tmp);
    }
    return true;
}



bool equal_owners(const std::vector<place> & a, const std::vector<place> & b){

    if(a.empty() || b.empty()){
        return false;
    }
    if(a.front().owner.empty() && b.front().owner.empty()){
        return true;
    }
    else if((!a.front().owner.empty() && b.front().owner.empty()) || (a.front().owner.empty() && !b.front().owner.empty())){
        return false;
    }
    size_t size;
    if(a.front().owner.size() < b.front().owner.size()){
        size = a.front().owner.size();
    }
    else if(a.front().owner.size() > b.front().owner.size()){
        size = b.front().owner.size();
    }
    else{
        size = a.front().owner.size();
    }

    for(size_t i = 0; i< size;i++){
        if(std::tolower(a.front().owner[i]) != std::tolower(b.front().owner[i]) ){
            return false;
        }
    }

    return true;
}

bool Compare_Owners(const std::vector<place> & a, const std::vector<place> & b){
    if(a.empty() || b.empty()){ //hz esli est smysl
        return false;
    }
    else if(a.front().owner.empty() && b.front().owner.empty()){
        return false;
    }
    else if(a.front().owner.empty() && !b.front().owner.empty()){
        return true;
    }

    size_t size;
    if(a.front().owner.size() < b.front().owner.size()){
        size = a.front().owner.size();
    }
    else if(a.front().owner.size() > b.front().owner.size()){
        size = b.front().owner.size();
    }
    else{
        size = a.front().owner.size();
    }

    for(size_t i = 0; i< size;i++){
        if(std::tolower(a.front().owner[i]) < std::tolower(b.front().owner[i]) ){
            return true;
        }
    }

    return false;
}

CIterator CLandRegister::listByOwner(const std::string &owner) const {
    std::vector<place> empty; // Create an empty vector for the case of no matches
    if (Owners.empty()) {
        return CIterator(empty, 0); // Return an iterator over an empty collection
    }

    // Your tmp setup looks correct for seeking the owner.
    place tmp("", "", "", 0, owner);
    std::vector<place> runner;
    runner.push_back(tmp);

    auto it_ownera = std::lower_bound(Owners.begin(), Owners.end(), runner, Compare_Owners);
    if (it_ownera == Owners.end() || it_ownera->empty() || !equal_owners(*it_ownera, runner)) {
        return CIterator(empty, 0); // Handle the case where no matching owner is found
    }

    // Now we can safely construct and return a CIterator as we have a valid vector.
    return CIterator(*it_ownera, 0);
}

size_t CLandRegister::count(const std::string &owner) const {
    place tmp("","","",0,owner);
    std::vector<place> runner;
    runner.push_back(tmp);
    if(Owners.empty()){return 0;}
    auto it_ownera = std::lower_bound(Owners.begin(), Owners.end(), runner, Compare_Owners);
    if(it_ownera == Owners.end() || !equal_owners(*it_ownera, runner) || it_ownera->empty()){return 0;}
    return it_ownera->size();

}

bool CLandRegister::newOwner(const std::string &region, unsigned int id, const std::string &owner) {
    place tmp("", "", region, id, "");
    if(RegionId.empty()){return false;}
    auto it_region = std::lower_bound(RegionId.begin(), RegionId.end(), tmp, Compare_region);
    if (it_region == RegionId.end()) {
        return false;
    }  if (it_region->region != region || it_region->id != id) {
        return false;
    }  if (it_region->owner == owner) {
        return false;
    }
    tmp.owner = it_region->owner;



    tmp.city = it_region->city;
    tmp.addr = it_region->addr;
    auto it_city = std::lower_bound(CityAddr.begin(), CityAddr.end(), tmp, compare_City);
    if (it_city == CityAddr.end()) {
        return false;
    } if (it_city->region != region || it_city->id != id) {
        return false;
    } if (it_city->owner == owner) {
        return false;
    }

    it_city->owner = owner;
    it_region->owner = owner;

    std::vector<place> runner;
    runner.push_back(tmp);
    auto it_vector_owners = std::lower_bound(Owners.begin(), Owners.end(), runner, Compare_Owners);

    if(it_vector_owners == Owners.end()){

  
        return true;

    }
    else if (equal_owners(*it_vector_owners, runner)) {


        size_t size = it_vector_owners->size();
        for (size_t i = 0; i < size; i++) {
            if ((*it_vector_owners)[i].region == region && (*it_vector_owners)[i].id == id) {
                it_vector_owners->erase(it_vector_owners->begin() + (long long)i);
                break;
            }
        }
        auto it_vector_owners2 = std::lower_bound(Owners.begin(), Owners.end(), runner, Compare_Owners);
        if (it_vector_owners2->empty()) {
            Owners.erase(it_vector_owners2);
        }

        tmp.owner = owner;
        //runner[0].owner = owner;
        std::vector<place> runner2;
        runner2.push_back(tmp);
        auto it_owner_new = std::lower_bound(Owners.begin(), Owners.end(), runner2, Compare_Owners);
        if (it_owner_new == Owners.end()) {
            Owners.push_back(runner2);
        } else if (equal_owners(*it_owner_new, runner2)) {
            it_owner_new->push_back(tmp);
        } else {
            Owners.insert(it_owner_new, runner2);
        }





    }
    return true;
}



bool CLandRegister::newOwner(const std::string &city, const std::string &addr, const std::string &owner) {
    place tmp(city,addr,"",0,"");
    if(CityAddr.empty()){return false;}
    auto it_city = std::lower_bound(CityAddr.begin(),CityAddr.end(), tmp, compare_City);
    if (it_city == CityAddr.end()) {
        return false;
    } if (it_city->city != city || it_city->addr != addr) {
        return false;
    }  if (it_city->owner == owner) {
        return false;
    }
    tmp.owner = it_city->owner;
    tmp.region = it_city->region;
    tmp.id = it_city->id;
    auto it_region = std::lower_bound(RegionId.begin(), RegionId.end(), tmp, Compare_region);
    if (it_region == RegionId.end()) {
        return false;
    }  if (it_region->city != city || it_region->addr != addr) {
        return false;
    }  if (it_region->owner == owner) {
        return false;
    }
    it_city->owner = owner;
    it_region->owner = owner;

    std::vector<place> runner;
    runner.push_back(tmp);
    auto it_vector_owners = std::lower_bound(Owners.begin(), Owners.end(), runner, Compare_Owners);


    if(it_vector_owners == Owners.end()){

        return true;

    }
    else  if (equal_owners(*it_vector_owners, runner)) {


        size_t size = it_vector_owners->size();
        for (size_t i = 0; i < size; i++) {
            if ((*it_vector_owners)[i].city == city && (*it_vector_owners)[i].addr == addr) {
                it_vector_owners->erase(it_vector_owners->begin() + (long long) i);
                break;
            }
        }

        auto it_vector_owners2 = std::lower_bound(Owners.begin(), Owners.end(), runner, Compare_Owners);
        if (it_vector_owners2->empty()) {
            Owners.erase(it_vector_owners2);
        }

        tmp.owner = owner;
        //runner[0].owner = owner;
        std::vector<place> runner2;
        runner2.push_back(tmp);
        auto it_owner_new = std::lower_bound(Owners.begin(), Owners.end(), runner2, Compare_Owners);
        if (it_owner_new == Owners.end()) {
            Owners.push_back(runner2);
        } else if (equal_owners(*it_owner_new, runner2)) {
            it_owner_new->push_back(tmp);
        } else {
            Owners.insert(it_owner_new, runner2);
        }



    }
    return true;
}

bool CLandRegister::getOwner(const std::string &city, const std::string &addr, std::string &owner) const {
    place tmp(city,addr,"",0,"");
    if(CityAddr.empty()){
        return false;
    }
    auto it_city = std::lower_bound(CityAddr.begin(),CityAddr.end(), tmp, compare_City);
    if (it_city == RegionId.end()) {
        return false;
    } else if (it_city->city != city || it_city->addr != addr) {
        return false;
    }


    owner = it_city->owner;
    return true;
}

bool CLandRegister::getOwner(const std::string &region, unsigned int id, std::string &owner) const {
    place tmp("", "", region, id, "");
    if(RegionId.empty()){return false;}
    auto it_region = std::lower_bound(RegionId.begin(), RegionId.end(), tmp, Compare_region);
    if (it_region == RegionId.end()) {
        return false;
    } else if (it_region->region != region || it_region->id != id) {
        return false;
    }


    owner = it_region->owner;
    return true;
}
bool CLandRegister::del(const std::string &region, unsigned int id) {
    place tmp("","",region,id,"");

    if(RegionId.empty()){return false;}
    auto it_region = std::lower_bound(RegionId.begin(), RegionId.end(),tmp, Compare_region);

    if(it_region==RegionId.end()){
        return false;
    }
    if(it_region->region != region || it_region->id!=id){
        return false;
    }

    tmp.city = it_region->city;
    tmp.addr = it_region->addr;
    tmp.owner = it_region->owner; //mozno ulucsit usaya novie structury

    RegionId.erase(it_region);

    auto it_city = std::lower_bound(CityAddr.begin(),CityAddr.end(), tmp, compare_City);
    if(it_city==CityAddr.end()){
        return false;
    }
     if(it_city->region != region || it_city->id!=id){
        return false;
    }

    CityAddr.erase(it_city);


    std::vector<place> runner;
    runner.push_back(tmp);

    auto it_owners = std::lower_bound(Owners.begin(), Owners.end(), runner, Compare_Owners);
    if(it_owners==Owners.end()){
        return true;
    }
    size_t size = it_owners->size();
    if(size == 1){
        Owners.erase(it_owners);
    }else{

        for(size_t i = 0; i<size; i++){
            if((*it_owners)[i].region == region && (*it_owners)[i].id ==id){
                it_owners->erase(it_owners->begin()+(long long)i);
                break;
            }
        }
    }


    return true;


}

bool CLandRegister::del(const std::string &city, const std::string &addr) {
    place tmp(city, addr, "", 0, "");

    if(CityAddr.empty()){
        return false;
    }
    auto it_city = std::lower_bound(CityAddr.begin(), CityAddr.end(),tmp, compare_City);

    if(it_city==CityAddr.end()){
        return false;
    }
    else if(it_city->city != city || it_city->addr!=addr){
        return false;
    }

    tmp.region = it_city->region;
    tmp.id = it_city->id;
    tmp.owner = it_city->owner;


    CityAddr.erase(it_city);

    auto it_region = std::lower_bound(RegionId.begin(),RegionId.end(), tmp, Compare_region);

    if(it_region==RegionId.end()){
        return false;
    }
    if(it_region->city != city || it_region->addr!=addr){
        return false;
    }
    RegionId.erase(it_region);
    std::vector<place> runner;
    runner.push_back(tmp);

    auto it_owners = std::lower_bound(Owners.begin(), Owners.end(), runner, Compare_Owners);
    if(it_owners==Owners.end()){
        return true;
    }
    size_t size = it_owners->size();
    if(size == 1){
        Owners.erase(it_owners);
    }else if(Owners.empty()){
        return false;
    }else{

        for(size_t i = 0; i<size; i++){
            if((*it_owners)[i].city == city && (*it_owners)[i].addr ==addr){ //mozhno po regionu i id
                it_owners->erase(it_owners->begin()+(long long)i);
                break;
            }
        }
    }


    return true;



}
static void test0 ()
{
    CLandRegister x;
    std::string owner;

    assert ( x . add ( "Prague", "Thakurova", "Dejvice", 12345 ) );
    assert ( x . add ( "Prague", "Evropska", "Vokovice", 12345 ) );
    assert ( x . add ( "Prague", "Technicka", "Dejvice", 9873 ) );
    assert ( x . add ( "Plzen", "Evropska", "Plzen mesto", 78901 ) );
    assert ( x . add ( "Liberec", "Evropska", "Librec", 4552 ) );
    CIterator i0 = x . listByAddr ();
    assert ( ! i0 . atEnd ()
             && i0 . city () == "Liberec"
             && i0 . addr () == "Evropska"
             && i0 . region () == "Librec"
             && i0 . id () == 4552
             && i0 . owner () == "" );
    i0 . next ();
    assert ( ! i0 . atEnd ()
             && i0 . city () == "Plzen"
             && i0 . addr () == "Evropska"
             && i0 . region () == "Plzen mesto"
             && i0 . id () == 78901
             && i0 . owner () == "" );
    i0 . next ();
    assert ( ! i0 . atEnd ()
             && i0 . city () == "Prague"
             && i0 . addr () == "Evropska"
             && i0 . region () == "Vokovice"
             && i0 . id () == 12345
             && i0 . owner () == "" );
    i0 . next ();
    assert ( ! i0 . atEnd ()
             && i0 . city () == "Prague"
             && i0 . addr () == "Technicka"
             && i0 . region () == "Dejvice"
             && i0 . id () == 9873
             && i0 . owner () == "" );
    i0 . next ();
    assert ( ! i0 . atEnd ()
             && i0 . city () == "Prague"
             && i0 . addr () == "Thakurova"
             && i0 . region () == "Dejvice"
             && i0 . id () == 12345
             && i0 . owner () == "" );
    i0 . next ();
    assert ( i0 . atEnd () );

    assert ( x . count ( "" ) == 5 );
    CIterator i1 = x . listByOwner ( "" );
    assert ( ! i1 . atEnd ()
             && i1 . city () == "Prague"
             && i1 . addr () == "Thakurova"
             && i1 . region () == "Dejvice"
             && i1 . id () == 12345
             && i1 . owner () == "" );
    i1 . next ();
    assert ( ! i1 . atEnd ()
             && i1 . city () == "Prague"
             && i1 . addr () == "Evropska"
             && i1 . region () == "Vokovice"
             && i1 . id () == 12345
             && i1 . owner () == "" );
    i1 . next ();
    assert ( ! i1 . atEnd ()
             && i1 . city () == "Prague"
             && i1 . addr () == "Technicka"
             && i1 . region () == "Dejvice"
             && i1 . id () == 9873
             && i1 . owner () == "" );
    i1 . next ();
    assert ( ! i1 . atEnd ()
             && i1 . city () == "Plzen"
             && i1 . addr () == "Evropska"
             && i1 . region () == "Plzen mesto"
             && i1 . id () == 78901
             && i1 . owner () == "" );
    i1 . next ();
    assert ( ! i1 . atEnd ()
             && i1 . city () == "Liberec"
             && i1 . addr () == "Evropska"
             && i1 . region () == "Librec"
             && i1 . id () == 4552
             && i1 . owner () == "" );
    i1 . next ();
    assert ( i1 . atEnd () );

    assert ( x . count ( "CVUT" ) == 0 );
    CIterator i2 = x . listByOwner ( "CVUT" );
    assert ( i2 . atEnd () );
    assert ( x . newOwner ( "Prague", "Thakurova", "CVUT" ) );
    assert ( x . newOwner ( "Dejvice", 9873, "CVUT" ) );
    assert ( x . newOwner ( "Plzen", "Evropska", "Anton Hrabis" ) );
    assert ( x . newOwner ( "Librec", 4552, "Cvut" ) );
    assert ( x . getOwner ( "Prague", "Thakurova", owner ) && owner == "CVUT" );

    assert ( x . getOwner ( "Dejvice", 12345, owner ) && owner == "CVUT" );
    assert ( x . getOwner ( "Prague", "Evropska", owner ) && owner == "" );
    assert ( x . getOwner ( "Vokovice", 12345, owner ) && owner == "" );
    //std::cout<<x . getOwner ( "Prague", "Technicka", owner )<<" a"<<owner<<"a"<<std::endl;
    assert ( x . getOwner ( "Prague", "Technicka", owner ) && owner == "CVUT" );
    assert ( x . getOwner ( "Dejvice", 9873, owner ) && owner == "CVUT" );
    assert ( x . getOwner ( "Plzen", "Evropska", owner ) && owner == "Anton Hrabis" );
    assert ( x . getOwner ( "Plzen mesto", 78901, owner ) && owner == "Anton Hrabis" );
    assert ( x . getOwner ( "Liberec", "Evropska", owner ) && owner == "Cvut" );
    assert ( x . getOwner ( "Librec", 4552, owner ) && owner == "Cvut" );
    CIterator i3 = x . listByAddr ();
    assert ( ! i3 . atEnd ()
             && i3 . city () == "Liberec"
             && i3 . addr () == "Evropska"
             && i3 . region () == "Librec"
             && i3 . id () == 4552
             && i3 . owner () == "Cvut" );
    i3 . next ();
    assert ( ! i3 . atEnd ()
             && i3 . city () == "Plzen"
             && i3 . addr () == "Evropska"
             && i3 . region () == "Plzen mesto"
             && i3 . id () == 78901
             && i3 . owner () == "Anton Hrabis" );
    i3 . next ();
    assert ( ! i3 . atEnd ()
             && i3 . city () == "Prague"
             && i3 . addr () == "Evropska"
             && i3 . region () == "Vokovice"
             && i3 . id () == 12345
             && i3 . owner () == "" );
    i3 . next ();
    assert ( ! i3 . atEnd ()
             && i3 . city () == "Prague"
             && i3 . addr () == "Technicka"
             && i3 . region () == "Dejvice"
             && i3 . id () == 9873
             && i3 . owner () == "CVUT" );
    i3 . next ();
    assert ( ! i3 . atEnd ()
             && i3 . city () == "Prague"
             && i3 . addr () == "Thakurova"
             && i3 . region () == "Dejvice"
             && i3 . id () == 12345
             && i3 . owner () == "CVUT" );
    i3 . next ();
    assert ( i3 . atEnd () );


    assert ( x . count ( "cvut" ) == 3 );
    CIterator i4 = x . listByOwner ( "cVuT" );
    assert ( ! i4 . atEnd ()
             && i4 . city () == "Prague"
             && i4 . addr () == "Thakurova"
             && i4 . region () == "Dejvice"
             && i4 . id () == 12345
             && i4 . owner () == "CVUT" );
    i4 . next ();
    assert ( ! i4 . atEnd ()
             && i4 . city () == "Prague"
             && i4 . addr () == "Technicka"
             && i4 . region () == "Dejvice"
             && i4 . id () == 9873
             && i4 . owner () == "CVUT" );
    i4 . next ();
    assert ( ! i4 . atEnd ()
             && i4 . city () == "Liberec"
             && i4 . addr () == "Evropska"
             && i4 . region () == "Librec"
             && i4 . id () == 4552
             && i4 . owner () == "Cvut" );
    i4 . next ();
    assert ( i4 . atEnd () );

    assert ( x . newOwner ( "Plzen mesto", 78901, "CVut" ) );
    assert ( x . count ( "CVUT" ) == 4 );
    CIterator i5 = x . listByOwner ( "CVUT" );
    assert ( ! i5 . atEnd ()
             && i5 . city () == "Prague"
             && i5 . addr () == "Thakurova"
             && i5 . region () == "Dejvice"
             && i5 . id () == 12345
             && i5 . owner () == "CVUT" );
    i5 . next ();
    assert ( ! i5 . atEnd ()
             && i5 . city () == "Prague"
             && i5 . addr () == "Technicka"
             && i5 . region () == "Dejvice"
             && i5 . id () == 9873
             && i5 . owner () == "CVUT" );
    i5 . next ();
    assert ( ! i5 . atEnd ()
             && i5 . city () == "Liberec"
             && i5 . addr () == "Evropska"
             && i5 . region () == "Librec"
             && i5 . id () == 4552
             && i5 . owner () == "Cvut" );
    i5 . next ();
    assert ( ! i5 . atEnd ()
             && i5 . city () == "Plzen"
             && i5 . addr () == "Evropska"
             && i5 . region () == "Plzen mesto"
             && i5 . id () == 78901
             && i5 . owner () == "CVut" );
    i5 . next ();
    assert ( i5 . atEnd () );

    assert ( x . del ( "Liberec", "Evropska" ) );
    assert ( x . del ( "Plzen mesto", 78901 ) );
    assert ( x . count ( "cvut" ) == 2 );
    CIterator i6 = x . listByOwner ( "cVuT" );
    assert ( ! i6 . atEnd ()
             && i6 . city () == "Prague"
             && i6 . addr () == "Thakurova"
             && i6 . region () == "Dejvice"
             && i6 . id () == 12345
             && i6 . owner () == "CVUT" );
    i6 . next ();
    assert ( ! i6 . atEnd ()
             && i6 . city () == "Prague"
             && i6 . addr () == "Technicka"
             && i6 . region () == "Dejvice"
             && i6 . id () == 9873
             && i6 . owner () == "CVUT" );
    i6 . next ();
    assert ( i6 . atEnd () );

    assert ( x . add ( "Liberec", "Evropska", "Librec", 4552 ) );
}

static void test1 ()
{
    CLandRegister x;
    std::string owner;

    assert ( x . add ( "Prague", "Thakurova", "Dejvice", 12345 ) );
    assert ( x . add ( "Prague", "Evropska", "Vokovice", 12345 ) );
    assert ( x . add ( "Prague", "Technicka", "Dejvice", 9873 ) );
    assert ( ! x . add ( "Prague", "Technicka", "Hradcany", 7344 ) );
    assert ( ! x . add ( "Brno", "Bozetechova", "Dejvice", 9873 ) );
    assert ( !x . getOwner ( "Prague", "THAKUROVA", owner ) );
    assert ( !x . getOwner ( "Hradcany", 7343, owner ) );
    CIterator i0 = x . listByAddr ();
    assert ( ! i0 . atEnd ()
             && i0 . city () == "Prague"
             && i0 . addr () == "Evropska"
             && i0 . region () == "Vokovice"
             && i0 . id () == 12345
             && i0 . owner () == "" );
    i0 . next ();
    assert ( ! i0 . atEnd ()
             && i0 . city () == "Prague"
             && i0 . addr () == "Technicka"
             && i0 . region () == "Dejvice"
             && i0 . id () == 9873
             && i0 . owner () == "" );
    i0 . next ();
    assert ( ! i0 . atEnd ()
             && i0 . city () == "Prague"
             && i0 . addr () == "Thakurova"
             && i0 . region () == "Dejvice"
             && i0 . id () == 12345
             && i0 . owner () == "" );
    i0 . next ();
    assert ( i0 . atEnd () );

    assert ( x . newOwner ( "Prague", "Thakurova", "CVUT" ) );
    assert ( ! x . newOwner ( "Prague", "technicka", "CVUT" ) );
    assert ( ! x . newOwner ( "prague", "Technicka", "CVUT" ) );
    assert ( ! x . newOwner ( "dejvice", 9873, "CVUT" ) );
    assert ( ! x . newOwner ( "Dejvice", 9973, "CVUT" ) );
    assert ( ! x . newOwner ( "Dejvice", 12345, "CVUT" ) );
    assert ( x . count ( "CVUT" ) == 1 );
    CIterator i1 = x . listByOwner ( "CVUT" );
    assert ( ! i1 . atEnd ()
             && i1 . city () == "Prague"
             && i1 . addr () == "Thakurova"
             && i1 . region () == "Dejvice"
             && i1 . id () == 12345
             && i1 . owner () == "CVUT" );
    i1 . next ();
    assert ( i1 . atEnd () );

    assert ( ! x . del ( "Brno", "Technicka" ) );
    assert ( ! x . del ( "Karlin", 9873 ) );
    assert ( x . del ( "Prague", "Technicka" ) );
    assert ( ! x . del ( "Prague", "Technicka" ) );
    assert ( ! x . del ( "Dejvice", 9873 ) );
}



int main() {
    test0();
    test1();

    /*  assert ( x . add ( "Prague", "Thakurova", "Dejvice", 12345 ) );
      assert ( x . add ( "Prague", "Evropska", "Vokovice", 12345 ) );
      assert ( x . add ( "Prague", "Technicka", "Dejvice", 9873 ) );
      assert ( ! x . add ( "Prague", "Technicka", "Hradcany", 7344 ) );
      assert ( ! x . add ( "Brno", "Bozetechova", "Dejvice", 9873 ) );
      assert ( !x . getOwner ( "Prague", "THAKUROVA", owner ) );
      assert ( !x . getOwner ( "Hradcany", 7343, owner ) );

      assert(!x.del("Pisya",2));
      assert(!x.newOwner("Kaka", "Puki","pisya"));
      assert(!x.getOwner("kaka","popa", owner) && owner=="");*/
    // CIterator a = x.listByOwner("daun");

    //CIterator b = x.listByAddr();

    return EXIT_SUCCESS;
}
