#include <iostream> 
#include <sys/shm.h> 
#include <sys/ipc.h> 
#include <cstring> 
#include <cerrno> 
#include <unistd.h> 
 
#define SHM_SIZE 1000 
#define MESSAGE "Hello world!" 
 
using namespace std; 
 
void check_error(int result, string action) { 
    if (result == -1) { 
        throw runtime_error("Error during " + action + " (" + to_string(errno) + "): " + strerror(errno)); 
    } 
} 
 
int main() { 
    try {
        key_t key = ftok(".", 'R'); 
        check_error(key, "generating key");
    
        int shm_id = shmget(key, SHM_SIZE, IPC_CREAT | 0666); 
        check_error(shm_id, "creating shared memory");
    
        char* shm_ptr = static_cast<char*>(shmat(shm_id, nullptr, 0)); 
        check_error((shm_ptr == (char*)-1) ? -1 : 0, "attaching shared memory");
    
        memcpy(shm_ptr, MESSAGE, strlen(MESSAGE)); 
    
        cout << key << endl; 

        check_error(shmdt(shm_ptr), "detaching shared memory");
    }
    catch (runtime_error& e) { 
        cerr << e.what() << endl; 
        return 1; 
    } 
 
    return 0; 

}