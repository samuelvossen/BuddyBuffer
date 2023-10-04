#include <iostream>
#include <unordered_map>
#include <string>
#include <bitset>
#include <fstream>
#include <vector>
//author sam vossen
//per your instructions i chose to do this in c++

class BufferManager {
private:
    std::bitset<8192> memory;
    std::unordered_map<size_t, size_t> free_buffers;

    size_t get_free_buffer(size_t size) {
        if (free_buffers.count(size) && free_buffers[size] > 0) {
            return size;
        }
        return 0;
    }

public:
    BufferManager() {
        free_buffers[510] = 10;
        free_buffers[254] = 0;
        free_buffers[126] = 0;
        free_buffers[62] = 0;
        free_buffers[30] = 0;
        free_buffers[14] = 0;
        free_buffers[6] = 0;
    }

    int request_buffer(size_t size) {
        size_t free_size = get_free_buffer(size);
        if (free_size == 0) {
            return -1;
        }

        free_buffers[free_size]--;
        return 2 + (10 - free_buffers[free_size] - 1) * free_size;
    }

    void return_buffer(int addr) {
        if (addr < 2) {
            return;
        }

        size_t size = (addr - 2) % 510;

        if (size == 0) {
            size = 510;
        }
        else if (size % 254 == 0) {
            size = 254;
        }
        else if (size % 126 == 0) {
            size = 126;
        }
        else if (size % 62 == 0) {
            size = 62;
        }
        else if (size % 30 == 0) {
            size = 30;
        }
        else if (size % 14 == 0) {
            size = 14;
        }
        else {
            size = 6;
        }

        free_buffers[size]++;
    }

    std::unordered_map<size_t, size_t> get_debug_info() {
        return free_buffers;
    }

    std::string get_status() {
        if (free_buffers[510] == 10) {
            return "Ok";
        }
        else if (free_buffers[510] == 0) {
            return "Tight";
        }
        else {
            return "Unknown";
        }
    }
};

int main() {

    // Redirect standard output to output.txt file
    std::ofstream out_file("output.txt");
    std::streambuf* coutbuf = std::cout.rdbuf(); // Save old buf
    std::cout.rdbuf(out_file.rdbuf()); // Redirect std::cout to output.txt











    BufferManager buf_manager;

    // Initializing buffers
    std::cout << "Samuel Vossen, 5.1.2023, Assignment 8" << std::endl;
    std::cout << "Initializing buffers" << std::endl;
    std::cout << "Expected values: 10 510 size buffers, Status Ok\n";
    std::cout << "Actual: \n";
    std::unordered_map<size_t, size_t> info = buf_manager.get_debug_info();
    for (const auto& entry : info) {
        std::cout << entry.second << " " << entry.first << " size buffers" << std::endl;
    }
    std::cout << "Status: \n" << buf_manager.get_status() << std::endl << std::endl;

    // Requesting a 510 size buffer
    std::cout << "Requesting a 510 size buffer" << std::endl;
    int buf1 = buf_manager.request_buffer(510);
    std::cout << "Buffer address: " << buf1 << std::endl;
    std::cout << "Expected values: 9 510 size buffers, Status Unknown\n";
    std::cout << "Actual: \n";
    info = buf_manager.get_debug_info();
    for (const auto& entry : info) {
        std::cout << entry.second << " " << entry.first << " size buffers" << std::endl;
    }
    std::cout << "Status: \n" << buf_manager.get_status() << std::endl << std::endl;

    // Returning the 510 size buffer
    std::cout << "Returning the 510 size buffer" << std::endl;
    buf_manager.return_buffer(buf1);
    std::cout << "Expected values: 10 510 size buffers, Status Ok\n";
    std::cout << "Actual: \n";
    info = buf_manager.get_debug_info();
    for (const auto& entry : info) {
        std::cout << entry.second << " " << entry.first << " size buffers" << std::endl;
    }
    std::cout << "Status: \n" << buf_manager.get_status() << std::endl << std::endl;

    // Requesting a non-existent buffer size
    std::cout << "Requesting a non-existent buffer size" << std::endl;
    int buf2 = buf_manager.request_buffer(1000);
    std::cout << "Buffer address: " << buf2 << std::endl;
    std::cout << "Expected values: -1 (no buffer found), Status Ok\n";
    std::cout << "Actual: \n";
    info = buf_manager.get_debug_info();
    for (const auto& entry : info) {
        std::cout << entry.second << " " << entry.first << " size buffers" << std::endl;
    }
    std::cout << "Status: \n" << buf_manager.get_status() << std::endl << std::endl;


    // Requesting all 510 size buffers
    std::cout << "Requesting all 510 size buffers" << std::endl;
    std::vector<int> buf_addresses;
    for (int i = 0; i < 10; ++i) {
        int addr = buf_manager.request_buffer(510);
        buf_addresses.push_back(addr);
        std::cout << "Buffer address " << i + 1 << ": " << addr << std::endl;
    }
    std::cout << "Expected values: 0 510 size buffers, Status Tight\n";
    std::cout << "Actual: \n";
    info = buf_manager.get_debug_info();
    for (const auto& entry : info) {
        std::cout << entry.second << " " << entry.first << " size buffers" << std::endl;
    }
    std::cout << "Status: \n" << buf_manager.get_status() << std::endl << std::endl;

    // Returning all 510 size buffers
    std::cout << "Returning all 510 size buffers" << std::endl;
    for (int i = 0; i < 10; ++i) {
        buf_manager.return_buffer(buf_addresses[i]);
    }
    std::cout << "Expected values: 10 510 size buffers, Status Ok\n";
    std::cout << "Actual: \n";
    info = buf_manager.get_debug_info();
    for (const auto& entry : info) {
        std::cout << entry.second << " " << entry.first << " size buffers" << std::endl;
    }
    std::cout << "Status: \n" << buf_manager.get_status() << std::endl << std::endl;

    // Requesting and returning buffers of different sizes
    std::cout << "Requesting and returning buffers of different sizes" << std::endl;
    for (int i = 0; i < 10; ++i) {
        int size = (i + 1) * 50;
        int addr = buf_manager.request_buffer(size);
        std::cout << "Requesting buffer of size " << size << ", address: " << addr << std::endl;
        buf_manager.return_buffer(addr);
        std::cout << "Returning buffer of size " << size << ", address: " << addr << std::endl;
        std::cout << "Status: " << buf_manager.get_status() << std::endl;
    }

    // Restore the original standard output buffer
    std::cout.rdbuf(coutbuf);

    return 0;
}
