#include "../headers/Subject.h"
#include "../headers/Observer.h"

void Subject::notify() {
    for(auto& ob : this->observers) {
        ob->update(this);
    }
}
void Subject::add(Observer* prog_observer) {
    this->observers.push_back(prog_observer);

}
void Subject::remove(Observer* prog_observer) {
    auto it = std::find(this->observers.begin(),this->observers.end(),prog_observer);
    if(it != this->observers.end()) this->observers.erase(it);
}