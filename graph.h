#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <sstream>

using namespace std;

//Person node that has all the details of the person
struct Person {
  string name;
  int Age;
  float spread;
  bool is_infected;
  bool is_sick;
  bool is_alive;
  int days;

  struct Person* next;
};


//Vertexlist class used to create the pointers for the adjacency list of each vertex
class VertexList {
  public:
  struct Person *head;
};


//Graph data structure
class Graph {
  public:
  int u, v, o;
  VertexList *v1;

  /*Initalizing variables in a constructor*/
  Graph(int m, int n) {
    this->u = m;
    this->v = n;
    this->o = 0;
    this->v1 = new VertexList[m];
  }

  /*Creating vertices from the population file to be given*/
  void insert_node(string filename){

    //filestream variable file
    fstream file;
    string word1, word2, word3;

    // opening file
    file.open(filename.c_str());

   // Create a list for n vertexes
    for(int k = 0; k < u; k++) {
      Person* newPerson = new Person;

      this->v1[k].head= newPerson;

      // extracting population information from the file
      while (file >> word1 >> word2 >> word3)
        {

        // converting content
        stringstream word(word2);
        stringstream words(word3);
        int age;
        float prob;

        word >> age;
        words >> prob;

        newPerson->name = word1;
        newPerson->Age = age;
        newPerson->spread = prob;
        if (this->o < age)
          this->o = age;

        break;

    }
  }

  file.close();
  }

  /*Creating Edges to link the vertices */
  void insert_edge(string filename){
    fstream file1;
    string src, dst;

    //opening file
    file1.open(filename.c_str());

    /*Joining all nodes to its head*/
    for(int k = 0; k < v; k++) {
      while (file1 >> src >> dst){
        findPerson(src)->next = findPerson(dst);
        break;

      }

    }
    file1.close();


  }

  /*auxillary method that helps find the nodes of connections*/
  Person* findPerson(string name){
    int k;
    bool z = false;
    for(k = 0; k<u; k++){
      if (v1[k].head->name == name){
        //z = true;
        break;
      }

    }

    return v1[k].head;
  }

  /*Method to print the graph*/
  void print(){
    for (int a = 0; a < u; a++){
      Person* tmp = v1[a].head;

      cout<<"\n Adjacency list of vertex "<<a<<"\n head ";
      while (tmp){
        cout<<"-> "<<tmp->name;
        tmp = tmp->next;
      }
    }
  }

/*Method to invect people if their simulation is positive*/
  void infect(Person* person){
    person->is_infected = true;

  }

  /*Recovery method for those who heal*/
  void recover(Person* tmp){
    tmp->is_infected = false;
    tmp->is_sick = false;
  }

  /*Method to get the disease probability using the maximum age*/
  float getDiseaseProb(Person* tmp){
    int a = tmp->Age;
    int b = this->o;

    return (float)a/(float)b;
    //return a;
  }

  /*method to make someone sick*/
  void makeSick(Person* tmp){
    tmp->is_sick = true;
    tmp->days++;
  }

  /*Method to eliminate those who die from the graph*/
  void is_dead(Person* tmp){
    for (int i = 0; i < u; i++){
      if (v1[i].head == tmp){
        v1[i].head = v1[i].head->next;
      }
    }
  }

  /*The method to infect the first person with the virus*/
  void infectRandom(){
    std::random_device fig;
    std::mt19937 gen(fig());
    std::uniform_int_distribution<> dis(1, u-1);
    int num = dis(gen);

    v1[num].head->is_infected = true;
}
};
/*
int getNumLines(string filename){

 string line;
 int count = 0;

  ifstream file;
  file.open(filename);

  while(!file.eof()) {
    getline(file, line);
	  count++;
  }

 //cout << sTotal;
 count--;
 file.seekg(0, ios::beg);
 file.close();
 return count;
}
*/