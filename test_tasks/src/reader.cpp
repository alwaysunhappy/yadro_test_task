#include <iostream> 
#include <sys/shm.h> 
#include <sys/ipc.h> 
#include <cstring> 
#include <cerrno> 
#include <unistd.h> 
 
#define SHM_SIZE 1000 
 
using namespace std; 
 
void check_error(int result, string action) {  
    if (result == -1) {  
        throw runtime_error("Error during " + action + " (" + to_string(errno) + "): " + strerror(errno));   
    }  
}  
 
int main() { 
    try {
    key_t key; 
    cin >> key; 
 
    int shm_id = shmget(key, SHM_SIZE, 0666); 
    check_error(shm_id, "accessing shared memory"); 
 
    char* shm_ptr = static_cast<char*>(shmat(shm_id, nullptr, 0)); 
    check_error((shm_ptr == (char*)-1) ? -1 : 0, "attaching shared memory"); 
 
    cout << "Data in shared memory: " << shm_ptr << endl; 
 
    check_error(shmdt(shm_ptr), "detaching shared memory"); 
 
    check_error(shmctl(shm_id, IPC_RMID, nullptr), "removing shared memory"); 
    }
    catch (runtime_error& e) { 
        cerr << e.what() << endl; 
        return 1; 
    } 
    return 0; 
}