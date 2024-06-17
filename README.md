# PA2-first-project
The task is to implement the CLandRegister class that will implement the land registry database.
Our simplified cadastre remembers the list of land plots and their respective owners. For each parcel we remember four pieces of information: cadastral area (region, string), parcel number in the cadastral area (ID, non-negative number), city (city, string) and address (addr, string). To identify a parcel, either a pair of data (region, ID) or a pair of data (city, addr) is needed. For example, a parcel may have the identification region=Dejvice, ID=12345. This pair of data uniquely identifies the parcel. The data region=Dejvice alone is not sufficient for identification (there may be multiple plots with different IDs in the cadastral area Dejvice), nor is ID=12345 (there may be multiple plots with this ID in different cadastral areas). By analogy, the pair city, addr identifies the land uniquely, but the city or addr itself does not. When comparing the strings region, city and addr, we distinguish between lower and upper case.

The owner of a parcel is identified by the string owner. One owner may own many different parcels, a parcel must always be owned by just one owner. Newly entered parcels are owned by the state (owner is an empty string). When comparing owner names, we do not distinguish between upper and lower case.

Over the plots and owners defined in this way, we want to build an interface for adding and deleting plots, setting owners and querying owners. The public interface of the CLandRegister class will be used for this:
A constructor without parameters.
  This constructor initializes an instance of the class so that the resulting instance is empty (contains no records).
Destructor.
  Releases the resources that the instance has allocated.
add(city, addr, region, id)
  method adds another parcel to the existing database. The parameters city and addr represent the city and address of the parcel, the parameters region and id specify the identification of the cadastral area and the number of the parcel in the cadastral area. The method     returns true if the record was added, or false if it was not added (because a record with the same pair (city,addr) or a record with the same pair (region,id) already existed in the database).
del (city, addr) / del (region,id)
  removes a record from the database. The parameter is uniquely identified by city and address (first option) or by cadastral area and ID(second option). If the record was actually removed, the method returns true. If the record has not been removed (because there was no    parcel with this identification), the method returns false. The ownership of the parcel does not affect the deletion. The eventual owner had a bad day.

getOwner (city, addr, owner) / getOwner (region, id, owner)
    finds the owner of the specified parcel. There are two options - the land is identified either by its address or by its cadastral area and ID. The owner parameter is output, the method places the owner's name in it. If the method succeeds, it returns true and sets the     output parameter owner. If the method fails (the parcel does not exist), it returns false and leaves the owner parameter unchanged. If the queried parcel is owned by the state (owner is an empty string), the method behaves the same as for any other owner (returns true     and sets the owner value, here to an empty string). Although we do not case-sensitive the method returns the owner's name exactly as it was entered (so you cannot internally convert owners to lower case, for example).
newOwner (city, addr, owner) / newOwner (region, id, owner)
    sets the new owner for the specified parcel to owner (the original owner is overwritten). There are two options - the parcel is identified either by its address or by its cadastral area and ID. If the method succeeds, it returns true. If the method fails (the parcel       does not exist, the specified parcel is already owned by the specified owner), it does not change anything in the records and returns false.
count (owner)
    finds the number of plots owned by the specified owner. The result is an integer, 0 if the specified owner does not own any of the parcels.
listByAddr()
    returns an iterator (see below) that can be used to traverse the list of all existing plots. The returned iterator will access plots sorted in ascending order by city, plots in the same city will be sorted by address.
listByOwner (owner)
    The method returns an iterator (see below) that can be used to traverse the list of plots owned by the specified owner owner. The returned iterator will access a list of the selected land in the order in which the owner acquired the land (starting with the earliest       acquired). If the owner does not own any land, the result will be an empty iterator (it will immediately report atEnd(), see below).
      copying constructor, assignment
The test environment does not copy CLandRegister instances, so there is no need to implement them. You can disable them for good sense in the source code (C++11 construct =delete).
The CIterator class is used to browse the list of plots. In the list of plots we always work with one selected plot from which we can find out its properties. We can move forward in the list and we can test if we are at the end of the list. This is the simplest version of the forward iterator. The interface of the iterator is:
atEnd
    The method will check if we have reached the last item in the list. If it returns true, then no more entries are available. If it returns false, we can use the methods to find out the properties of the plots and can move on to the next entry. A typical use of an         iterator in a while loop tests the while condition ( ! it . atEnd() ), accesses the plot properties in the loop body, and calls it . next() at the end of the loop body to move to the next record.
next
    This method moves the iterator to the next plot in the list.
city
    The method gets the name of the city of the currently selected parcel.
addr
    The method finds the address of the currently selected parcel.
region
    The method finds the cadastral territory of the currently selected parcel.
id
    The method finds the number of the parcel in the cadastral territory.
owner
  Metoda zjistí vlastníka vybraného pozemku.

konstruktor, destruktor, kopírující konstruktor
testovací prostředí iterátory nekopíruje, používá je pouze pro jednorázový průchod seznamem vrácených pozemků. Instance iterátoru jsou vyráběné pouze Vašimi metodami, tyto instance jsou vracené jako návratové hodnoty metod listByAddr / listByOwner. Při navracení z těchto hodnot mohou být volané kopírující nebo přesouvací konstruktory, záleží na implementaci. Obecně je lepší v iterátoru neukládat dynamicky alokovaná data. Pro implementaci stačí mít v iterátoru dvě hodnoty (pozici v poli a odkaz na CLandRegister). Implementací kopírujícího konstruktoru se pak nemusíte zdržovat.
modifikace
testovací prostředí neprovádí žádné modifikace instance CLandRegister v době, kdy používá CIterator. Tedy můžete se spolehnout, že nejprve iterátor dosáhne atEnd a teprve následně může být měněna instance CLandRegister. Díky tomu si iterátor nemusí data kopírovat z CLandRegister, ale může na ně pouze odkazovat.    
