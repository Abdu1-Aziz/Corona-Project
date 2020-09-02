#include <iostream>
#include <string>
#include <time.h>
#include <random>
#include <cstdlib>
#include "graph.h"
using namespace std;

/* You can use this function to simulate
probabilities */

bool simulate_prob(float prob){

  prob = prob*1000;

  std::random_device dev;
  std::mt19937 rng(dev());
  std::uniform_int_distribution<std::mt19937::result_type> random_number(1,1000); // distribution in range [1, 1000]

  if ( random_number(rng) <= prob)
    return true;

  return false;
}

int main(){

    /* The number of days simulation will run for */
    int days_to_simulate = 100;
    /*Initiation of counters for the number of people at each state of the disease*/
    int num_infected = 0;
    int num_sick = 0;
    int num_recovered = 0;
    int num_dead = 0;

    /* Ask the user for the population and
    connections files */
    cout << "Welcome to CoronaSim!" << endl;
    string pop_file, conn_file;
    cout << "Enter population file name: ";
    cin >> pop_file;
    cout << "Enter connections file name: ";
    cin >> conn_file;

    // TODO: Populate your graph data structure
    bool is_populated = false;

    if (is_populated)
        cout << "File Loaded!" << endl;

        /*Taking more information to tailor the graph to the files provided*/
        int num_people, num_conn;

        cout<<"How many lines are in your population: ";
        cin>> num_people;

        cout<<"How many links are in your connections: ";
        cin>> num_conn;

        /*Creating the graph data structure for the information provided*/
        Graph gh(num_people, num_conn);

        /*Inserting vertices for the graph*/
        gh.insert_node(pop_file);

        /*Joining the vertices with edges to form a full graph*/
        gh.insert_edge(conn_file);


    while(true){

        int choice;

        /* Print menu of things that your application can do*/
        cout << "*** *** *** *** *** *** *** *** *" << endl;
        cout << "What would you like to do?" << endl;
        cout << "1. Print population" << endl;
        cout << "2. Simulate" << endl;
        cout << "3. Summarize population" << endl;
        cout << "4. Implement policy and simulate" << endl;
        cout << "5. Exit" << endl;
        cout << "*** *** *** *** *** *** *** *** *" << endl;
        cout << "Your selection: ";

        /* TODO: You should feel free to add other
        items to the menu above for your demo video */

        cin >> choice;

        /*Ideally inside the various cases of the switch
        statement below, you will call specific functions
        supported by your graph data structure and your
        simulation algorithm. You can design all these
        functions as you like.*/

        switch(choice){

            case 1:
            {

                /* TODO: Print your population. Use
                any format you like.*/

                /*Printing the content of the graph created*/
                gh.print();
                cout<<endl;
                break;
            }
            case 2:
            {

                /* TODO: Run simulation as described
                in the handout.*/

                /*Infecting a random person in the population*/

                cout<<endl;
                cout<<"Running Simulation..."<<endl;
                cout<<endl;

                gh.infectRandom();
                num_infected +=1;

                for (int i = 0; i <days_to_simulate; i++){
                    for (int j = 0; j < num_people; j++){

                        Person* person = gh.v1[j].head;
                        if (person->is_infected == true && person->is_sick == false){
                            float disease_prob = gh.getDiseaseProb(person);

                            /*Simulating disease probability to see whether the person will fall sick*/
                            if (simulate_prob(disease_prob)){
                                gh.makeSick(person);
                                num_sick+=1;
                            }
                        }

                        /*Simulating the person's spread probability to see whether they should be infected*/

                        if (person->is_infected == true && simulate_prob(person->spread)){
                            while (person->next != NULL){
                                gh.infect(person->next);
                                person = person->next;
                                num_infected+=1;
                            }
                        }

                        /*checking the number of days of sick people to see if they have reached their lifespan*/
                        if (person->is_sick == true && person->days > 7){
                            if(person->next != NULL){
                                gh.is_dead(person);
                            }else{
                                person = NULL;
                            }
                            num_dead+=1;
                        }


                        if (person->is_infected == true && person->is_sick == true){
                            float inverse_prob = 1 - gh.getDiseaseProb(person);
                            if (simulate_prob(inverse_prob)){
                                gh.recover(person);
                                num_recovered+=1;
                            }else{
                                person->days+=1;
                            }
                        }

                    }

                   /* cout<<"---Day "<<i+1<<" Summary----"<<endl;
                    cout<<"Number of infections: "<<num_infected<<endl;
                    cout<<"Number of sick people: "<<num_sick<<endl;
                    cout<<"Number of recoveries: "<<num_recovered<<endl;
                    cout<<"Number of deaths: "<<num_dead<<endl;*/
                }

                cout<<endl;
                cout<<"------Done Simulating------"<<endl;
                cout<<endl;
                cout<<"*****Check for population summary*****"<<endl;
                cout<<endl;

                break;
            }
            case 3:

                /* TODO: Print a summary of the population
                here. Design the summary as you like.
                Print at least the number of people
                infected, sick, recovered, dead etc.*/

                cout<<"Coronavirus Update"<<endl;
                cout<<endl;
                cout<<"Number of infections: "<<num_infected;
                cout<<endl;
                cout<<"Number of people sick: "<<num_sick;
                cout<<endl;
                cout<<"Number of recoveries: "<<num_recovered;
                cout<<endl;
                cout<<"Number of deaths: "<<num_dead;
                cout<<endl;

                num_infected = 0;
                num_sick = 0;
                num_recovered = 0;
                num_dead = 0;

                break;

            case 4:
            {

                /* TODO: Implement your own policy and
                re-simulate.*/
                cout<<"Implementing Compulsory Face Musk Policy ..."<<endl;


                /*Infecting a random person in the population*/
                gh.infectRandom();
                num_infected +=1;

                for (int i = 0; i <days_to_simulate; i++){
                    for (int j = 0; j < num_people; j++){

                        Person* person = gh.v1[j].head;
                        if (person->is_infected == true && person->is_sick == false){
                            float disease_prob = gh.getDiseaseProb(person);

                            /*Simulating disease probability to see whether the person will fall sick*/
                            if (simulate_prob(disease_prob)){
                                gh.makeSick(person);
                                num_sick+=1;
                            }
                        }

                        /*Simulating the person's spread probability to see whether they should be infected*/

                        if (person->is_infected == true && simulate_prob(person->spread-0.1)){
                            while (person->next != NULL){
                                gh.infect(person->next);
                                person = person->next;
                                num_infected+=1;
                            }
                        }

                        /*checking the number of days of sick people to see if they have reached their lifespan*/
                        if (person->is_sick == true && person->days > 7){
                            if(person->next != NULL){
                                gh.is_dead(person);
                            }else{
                                person = NULL;
                            }
                            num_dead+=1;
                        }


                        if (person->is_infected == true && person->is_sick == true){
                            float inverse_prob = 1 - gh.getDiseaseProb(person);
                            if (simulate_prob(inverse_prob)){
                                gh.recover(person);
                                num_recovered+=1;
                            }else{
                                person->days+=1;
                            }
                        }

                    }
                }


                cout<<endl;
                cout<<"Running Simulation..."<<endl;
                cout<<endl;

                cout<<endl;
                cout<<"------Done Simulating------"<<endl;
                cout<<endl;
                cout<<"*****Check for population summary*****"<<endl;
                cout<<endl;

                break;
            }
            case 5:

                /* TODO: Here de-allocate all dynamically
                allocated variables before exiting*/
                return 0; // exiting
        }
    }

}

