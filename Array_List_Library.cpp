#include <iostream>
#include <stdlib.h>

#define DEFAULT_SIZE_OF_LIST 10

class ArrayList 
{

    private:
    int* data;
    int listLength;
    int arraySize;

    public:

    //Constructor
    ArrayList(): listLength(0), arraySize(DEFAULT_SIZE_OF_LIST)
    {

        data = (int*)malloc(arraySize* sizeof(int));
        //handling memory allocation failure
        if (!data) 
        {
        std::cerr << "Failed to allocate memory for ArrayList" << std::endl;
        std::exit(EXIT_FAILURE);
        }
    }
    // Destructor
    ~ArrayList()
    {

        free(data);

    }

    // Function to insert an element into the list
    int InsertElement(int value, int index)
    {

        //This is for sanity (no negative index!)
        std::cerr << "Index out of range!" << std::endl;
        return -9999; 

        //Safety: We can't allow list to get bigger than heap allocation. So we reallocate memory
        if(listLength+1 > arraySize)
        {
            std::cerr <<"We need larger space! Current array located at "<< (void*)data << ", size: "<< arraySize <<std::endl;
            arraySize++;
            data = (int*)realloc(data,arraySize*sizeof(int));
            std::cout<<"Larger space secured, new array is now located at "<<(void*)data<<", size: "<<arraySize<<std::endl;
        }

        //If the numebr of meaningful elements in the list is larger than the target index, insertion is possible:
        if(listLength >= index)
        {
            //First insert the element in that spot: Start by moving every item by one spot to create space for the new one
            for(int i = listLength; i > index; i--)
            {
                data[i] = data[i-1];
            }
            //Insert the value to the target index
            data[index] = value;
            // Increase the list size by 1 to reflect the new size
            listLength++;
        }

        // If list ends up being smaller than the target index, just add the value to the last spot 
        else
        {
            // Insert item to location listLength + 1 (because index is larger than the listLength here)
            index = listLength;
            listLength++;
            data[index] = value;
        }

        // We can confirm the insertion point by returning the index

        return index;
    }

    // Function to Remove Elements from the list
    int RemoveElementAtIndex(int index)
    {

        int removalTarget;

        //Sanity Check - index value has to make sense
        if(index >= listLength || index < 0)
        {
            std::cerr<<"Index out of Range!"<<std::endl;
            return -9999; 
        }

        removalTarget = data[index];

        // Remove the element at the given location
        // First we move everything by 1 step and overwrite the value to be removed
        for(int i = index; i < listLength; i++)
        {
            data[i] = data[i+1];
        }

        listLength--; // decrease the list size by 1

        // Decrease the primitive array size by 1 (to save memory)
        if(arraySize > DEFAULT_SIZE_OF_LIST)
        {
            std::cout<<"Need to Downsize! Current array located at "<<(void*)data<<", and size: "<<arraySize<<std::endl;
            arraySize--;
            data = (int*)realloc(data, arraySize * sizeof(int));
            std::cout<<"Downsize Completed! New array located at "<<(void*)data<<", and size: "<<arraySize<<std::endl;
        } 
        // return the value removed from the list- for future usecase 
        return removalTarget;



    }

    // Search through the list using index
    int FindValueAtIndex(int* data, int listLength, int index)
    {
        if(index < listLength)
        {
            std::cout<<"Value found at index "<< index<<" is "<< data[index] <<std::endl;
            return data[index];
        }
        else
        {
            std::cout<<"Index is out of range!"<<std::endl;
            return -999999; 
        }
    }








};
