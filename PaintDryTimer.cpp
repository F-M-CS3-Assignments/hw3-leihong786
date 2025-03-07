#include <ctime>    
#include <iostream>  
#include <cmath>     
#include <vector>    
#include <cstdlib>   
#include <cassert>   
#include <memory>    
#include <cctype>    
#include "TimeCode.h" 

using namespace std;

/**
 * Struct representing an object being tracked for drying.
 * - `name`: Unique name identifier.
 * - `startTime`: Time when drying started.
 * - `timeToDry`: Smart pointer to a `TimeCode` object representing drying duration.
 */
struct DryingSnapShot {
    string name;
    time_t startTime;
    unique_ptr<TimeCode> timeToDry;
};

/**
 * Calculates the remaining drying time for an object.
 * Returns 0 if the drying period has elapsed.
 */
long long int get_time_remaining(const DryingSnapShot& dss) {
    long long elapsed = time(0) - dss.startTime;
    return max(0LL, static_cast<long long>(dss.timeToDry->GetTimeCodeAsSeconds()) - elapsed);
}

/**
 * Converts a DryingSnapShot into a readable string.
 */
string drying_snap_shot_to_string(const DryingSnapShot& dss) {
    TimeCode remainingTime(0, 0, get_time_remaining(dss));
    return dss.name + " takes " + dss.timeToDry->ToString() + " to dry, " + remainingTime.ToString() + " remaining";
}

/**
 * Computes the surface area of a sphere given its radius.
 * Formula: Surface Area = 4 * π * r²
 */
double get_sphere_sa(double radius) {
    return 4 * M_PI * pow(radius, 2);
}

/**
 * Creates a unique `TimeCode` object based on the surface area of the object.
 * Drying time is proportional to the surface area.
 */
unique_ptr<TimeCode> compute_time_code(double surfaceArea) {
    return make_unique<TimeCode>(0, 0, static_cast<long long unsigned int>(surfaceArea));
}

/**
 * Runs tests to validate core functionality.
 */
void tests() {
    // Test get_time_remaining()
    DryingSnapShot dss;
    dss.startTime = time(0);
    dss.timeToDry = make_unique<TimeCode>(0, 0, 7);
    assert(get_time_remaining(dss) > 6 && get_time_remaining(dss) < 8);

    // Test get_sphere_sa()
    double sa = get_sphere_sa(2.0);
    assert(50.2654 < sa && sa < 50.2655);

    // Test compute_time_code()
    auto tc = compute_time_code(1.0);
    assert(tc->GetTimeCodeAsSeconds() == 1);

    cout << "ALL TESTS PASSED!" << endl;
}

int main() {
    
    tests();

    vector<DryingSnapShot> vec;
    string input;
    int tracker = 0;

    cout << "Choose an option: (A)dd, (V)iew Current Items, or (Q)uit: ";
    cin >> input;

    if (!input.empty()) {
        input[0] = tolower(input[0]);
    }

    while (input != "q") { // Quits if 'q' is entered
        if (input == "a") {
            cout << "Radius: ";
            cin >> input;

            try {
                double radius = stod(input);
                if (radius <= 0) {
                    throw invalid_argument("Radius must be positive.");
                }

                tracker++;
                DryingSnapShot dss;
                dss.name = "Object " + to_string(tracker);
                dss.startTime = time(0);
                dss.timeToDry = compute_time_code(get_sphere_sa(radius));
                vec.push_back(move(dss));

                cout << drying_snap_shot_to_string(vec.back()) << endl;
            } catch (const invalid_argument&) {
                cout << "Error: Please enter a valid positive number.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        } else if (input == "v") {
            if (vec.empty()) {
                cout << "No drying objects being tracked.\n";
            } else {
                auto it = vec.begin();
                while (it != vec.end()) {
                    if (get_time_remaining(*it) == 0) {
                        it = vec.erase(it);  // Remove expired drying objects
                    } else {
                        cout << drying_snap_shot_to_string(*it) << endl;
                        ++it;
                    }
                }
                cout << vec.size() << " batches being tracked.\n";
            }
        } else {
            cout << "Invalid choice. Please enter A, V, or Q.\n";
        }

        cout << "Choose an option: (A)dd, (V)iew Current Items, or (Q)uit: ";
        cin >> input;

        if (!input.empty()) {
            input[0] = tolower(input[0]);
        }
    }

    cout << "User quit. Program exiting.\n";
    return 0;
}
