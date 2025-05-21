#include "db.h"
// ---------------------------------------------
// SNode class
// Default constructor
// TODO DONE: Implement this
// BASIC function header is provided for so that the code will compile
// The actual function header may be different 

//track total students
unsigned int SNode::num_students = 0;

SNode::SNode() 
    : Node(++num_students)
{
    first = "";
    last = "";
    age = 0;
    
}

// Constructor
// TODO DONE: Implement this
// BASIC function header is provided for so that the code will compile
// The actual function header may be different 

SNode::SNode(string f_, string l_, unsigned int a_)
    : Node(++num_students)
{
    first = f_;
    last = l_;
    age = a_;
}

// Destructor
SNode::~SNode()
{
// TODO: Implement this
}

// Public interface
void SNode::change_first(string f_)
{
    first = f_;
// TODO DONE: Implement this
} 
void SNode::change_last(string l_)
{
    last = l_;

// TODO DONE: Implement this
} 
string SNode::get_first()
{
    return first;
// TODO DONE: Implement this
}

string SNode::get_last()
{
    return last;
// TODO DONE: Implement this
}

unsigned int SNode::get_age()
{
    return age;
// TODO DONE: Implement this
}

// Print information about the student
// do not change this
void SNode::print_info(ostream& to)
{
    to << "Student ID: " << this->get_key()
       << "\tFirst: " << this->first
       << "\tLast: " << this->last
       << "\tAge: " << this->age << endl;
}
// ---------------------------------------------
