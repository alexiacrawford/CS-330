#include <iostream>

using namespace std;


class Athlete {

	protected:
	    string sport;

	public:

		Athlete(string s){sport = s;}

		virtual void displayInfo() {
        	cout << "I play " << sport << endl;}

        virtual ~Athlete() {cout << "I'm announcing my retirement!" << endl;}

};

class Basketball : public Athlete {

	private:
		string name;
	public:
		Basketball(string n) : Athlete("basketball"), name(n) {}
		void displayInfo() override;
		friend class Baseball;	

};


// Child Class baseball
class Baseball : public Athlete {

	public:
		Baseball() : Athlete("baseball"){}		
		void get_friends_name(Basketball &b);
		~Baseball() {cout << "I'm a retired baseball player!" << endl;}


};


// Function
void Baseball::get_friends_name(Basketball &b){

	cout << "My friend's name is " << b.name << endl;

}


void Basketball::displayInfo() {

    cout << "I play " << sport << " and my name is " << this->name << endl;

}


int main(){


	Athlete a("soccer");
	Baseball *b = new Baseball();
	Basketball c("Dribble");

	a.displayInfo();
	b->displayInfo();
	c.displayInfo();

	b->get_friends_name(c);

	delete b;


}





