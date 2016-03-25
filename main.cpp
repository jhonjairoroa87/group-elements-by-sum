#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

// print variable name and value
void print_variable(string var_name, int var_value){
    cout << "value of " << var_name << " : " << var_value << endl;
}

// print elements contained in an array
void print_array(int *my_array, int array_length){
    cout << "[ ";
    for( int i = 0; i < array_length; i++){
        cout << my_array[i] << " ";
    }
    cout << "]"<< endl;
}

// print elemens contained in a vector
void print_vector(vector<int*> my_vector, int group_length){
    for (std::vector<int*>::iterator it = my_vector.begin() ; it != my_vector.end(); ++it){
        int* my_array = *it;
        print_array(my_array, group_length);
    }
}

// sum elements that are in an array
// params:
//  - my_array: array to be iterated and its elements will be summed. Ie, [1,2,3,4,5]
//  - array_length: length of the given array. Ie, 5
// return sum of the array elements. Ie 15
int sum_array(int *my_array, int array_length){
    int sum_value = 0;
    for( int i = 0; i < array_length; i++){
        sum_value = sum_value + my_array[i];
    }
    return sum_value;
}

// Create a subgroup of the given array selecting the elements based on the provided indexes
//  - my_array: array to be iterated and its elements will be summed. Ie, [1,2,3,4,5,6,7,8,9,10]
//  - group_length: Length of the groups to be created. Ie 3
//  - indexes_array: array of indexes to be iterated and its elements will be summed. Ie, [1,2,3,4,5,6,7,8,9,10]
// return subgroup. Ie [4,5,9]
int* create_array_group(int *my_array, int group_length, int *indexes_array){
    int* array_group = new int[group_length];
    for( int i = 0; i < group_length; i++){
        int my_array_index = indexes_array[i];
        int array_value = my_array[my_array_index];
        array_group[i] = array_value;
    }
    return array_group;
}

// build the indexes that are going to be iterated doing the combination changing the last element of
// the group
// params:
//  - array_length: Length of the array that contains the elements to be grouped. Ie 10
//  - group_length: Length of the groups to be created. Ie 3
//  - init_index: Starting point of the indexes to be identified. Ie 2
// return example : <[0,1,2], [0,1,3], [0,1,4], [0,1,5], [0,1,6], [0,1,7]>
vector <int*> get_indexes_vectors(int array_length, int group_length, int init_index){

    vector <int*> indexes_vector;
    int *group_array = new int[group_length];

    // first index array
    for( int i = 0; i < group_length; i++){
        group_array[i] = i+init_index;
    }

    // define the other indexes
    int current_index = group_array[group_length-1];
    while( current_index < array_length ){
        int *new_group_array = new int[group_length];
        new_group_array[0] = group_array[0];
        new_group_array[1] = group_array[1];
        new_group_array[2] = current_index;
        indexes_vector.push_back( new_group_array );
        current_index++;
    }

    return indexes_vector;
}

// Merge given vectors
// params:
// - indexes_vector_1: first vector to be merged. Ie <[1,2],[3,4]>
// - indexes_vector_2: second vector to be merged. Ie <[5,6],[7,8]>
// return vector taht contain the elements of the given vectors. Ie <[1,2],[3,4],[5,6],[7,8]>
vector <int*> merge_vectors (vector <int*> indexes_vector_1, vector <int*> indexes_vector_2){
    vector <int*> final_indexes_vector = indexes_vector_1;
    final_indexes_vector.insert(final_indexes_vector.end(), indexes_vector_2.begin(), indexes_vector_2.end());
    return final_indexes_vector;
}

// build all indexes that are going to be iterated
// params:
//  - array_length: Length of the array that contains the elements to be grouped. Ie 10
//  - group_length: Length of the groups to be created. Ie 3
// return example : <[0,1,2], [0,1,3], [0,1,4], [1,2,3], [1,2,4], [1,2,5], [2,3,4], [2,3,5], [2,3,6]>
vector <int*> get_complete_indexes_vectors(int array_length, int group_length){
    vector <int*> final_indexes_vector;
    for( int i = 0; i < array_length; i++){
        vector <int*> indexes_vector = get_indexes_vectors(array_length, group_length, i);
        final_indexes_vector = merge_vectors(final_indexes_vector, indexes_vector);
    }
    // uncomment to see the total indexes vector
    // print_variable("final_indexes_vector", 0);
    // print_vector(final_indexes_vector, group_length);
    return final_indexes_vector;
}

// validate if the group elements match the sum criteria
// params:
//  - init_array: array to be iterated and its elements will be summed. Ie, [1,2,3,4,5,6,7,8,9,10]
//  - array_length: Length of the array that contains the elements to be grouped. Ie 10
//  - group_length: Length of the groups to be created. Ie 3
//  - group_sum: Value the valid group elements should be equal. Ie 9
// return vector that contains the group. Ie <[1,2,6], [2,3,4]>
vector <int*> iterare_main_array(int *init_array, int array_length, int group_length, int group_sum){
    vector <int*> result_vector;
    vector <int*> indexes_vector = get_complete_indexes_vectors(array_length, group_length);
    // iterate the indexes to cerate the group and validate it sum value
    for (std::vector<int*>::iterator it = indexes_vector.begin() ; it != indexes_vector.end(); ++it){
        int* my_index_array = *it;
        int* values_group = create_array_group(init_array, group_length, my_index_array);
        // validate if the elements of the group sums the expected value
        if (sum_array(values_group, group_length) == group_sum){
            result_vector.push_back( values_group );
        }
    }
    return result_vector;
}

int main() {

    int array_length = 10; // number of elements the array will contain
    int numbers [array_length] = { 8, 4, 3, 2, 5, 6, 7, 1, 9, 10 }; // numbers to be grouped
    int group_length = 3;
    int group_sum = 9;

    // sort from lower to greater value
    sort(numbers, numbers + array_length);
    // create the groups and identiby the ones that math the sum criteria
    vector <int*> result_vector = iterare_main_array(numbers, array_length, group_length, group_sum);
    print_vector(result_vector, group_length);

    return 0;
}
