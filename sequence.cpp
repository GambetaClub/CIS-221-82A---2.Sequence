// Provided by:   ____________(Mariano Jalif)__________
// Lab:           ____________(-)________
// Course number: ____________(CIS-221-82A)________

// I haven't neither shown nor copied code from/to anybody.
// I also state that I typed everything in this code on my own.
// I haven't watched anyone's code.

// VALUE SEMANTICS for the Statistician class:
// Assignments and the copy constructor may be used with Statistician objects.
#include "sequence.h"
#include <cassert>

namespace main_savitch_4
{   
    // CONSTRUCTOR
    // Postcondition: The sequence has been initialized as an empty sequence.
    // The insert/attach functions will work efficiently (without allocating
    // new memory) until this capacity is reached.
   sequence::sequence(size_type initial_capacity)
   {
       // Initialazing member variables.
       used_ = 0;
       current_index_ = 0;
       data_ = new value_type[initial_capacity];
       capacity_ = initial_capacity;
   }

    // COPY CONSTRUCTOR
    // Postcondition: The sequence has been initialized to the sequence
    //   passed in.
    // The insert/attach functions will work efficiently (without allocating
    // new memory) until the source's capacity is reached.
   sequence::sequence(const sequence& source)
   {    
        // Creating the a new dinamic array.
        data_ = new value_type[source.capacity_];
        // Setting the values of source to the array.
        for (size_t i = 0; i < source.used_; i++){
            data_[i] = source.data_[i];
        }
        // Copying the attributes of source to the array.
        current_index_ = source.current_index_;
        capacity_ = source.capacity_;
        used_ = source.used_;
   }

    // DESTRUCTOR
    // Postcondition: The memory allocated for the object has been released.
   sequence::~sequence( )
   {
        // Deleting the data allocated for the object.
        delete [] data_;
   }


    // MODIFICATION MEMBER FUNCTIONS


    // Postcondition: The sequence's current capacity is changed to the 
    //   new_capacity (but not less that the number of items already on the
    //   list). The insert/attach functions will work efficiently (without
    //   allocating new memory) until this new capacity is reached.
   void sequence::resize(size_type new_capacity)
   {
        // Making sure that it makes sense to call the function.
        if((new_capacity > capacity_) || (used_ <= new_capacity)){
            capacity_ = new_capacity;

            // Creating a new array for changing the size of the original sequence.
            value_type* newData;
            newData = new value_type[new_capacity];

            // Copying the data from the original array to the new one.
            for (size_t i = 0; i < used_; i++){
                newData[i] = data_[i];
            }

            // Deleting the array from original sequence.
            delete [] data_;

            // Setting the new array to the sequence. 
            data_ = newData;
        }
   }

    // Postcondition: The first item on the sequence becomes the current item
    //   (but if the sequence is empty, then there is no current item).
   void sequence::start( )
    {   
        current_index_ = 0;
    }

    // Postcondition: If the current item was already the last item in the
    //   sequence, then there is no longer any current item. Otherwise, the new
    //   current item is the item immediately after the original current item.
    void sequence::advance( )
    {
        current_index_++;
    }

    // Postcondition: A new copy of entry has been inserted in the sequence
    //   before the current item. If there was no current item, then the new
    //   entry has been inserted at the front of the sequence. In either case,
    //   the newly inserted item is now the current item of the sequence.
    void sequence::insert(const value_type& entry)
    {
        // Increments capacity of array if it's necessary.
        if (used_ == capacity_){
            resize(capacity_ + 1);
        }

        // Sets current index to the front if there is no current item.
        if (!is_item()){
            current_index_ = 0;
        }

        // Moves data up for inserting "entry"
        if (used_ > 0){
            move_down(current_index_);
        }

        // Inserts entry in the array.
        data_[current_index_] = entry;

        // Increments the number of spots used in the array.
        used_++;
    }

    // Postcondition: A new copy of entry has been inserted in the sequence
    //   after the current item. If there was no current item, then the new
    //   entry has been attached to the end of the sequence. In either case,
    //   the newly inserted item is now the current item of the sequence.
    void sequence::attach(const value_type& entry)
    {
        // Increments capacity of array if it's necessary.
        if (used_ == capacity_){
            resize(capacity_ + 1);
        }

        // Sets current index to the front if there is no current item.
        if (!is_item()){
            current_index_ = used_;
        } else{
            // Sets current index where entry should be.
            current_index_++;

            // Moves the data down if there is any number in the sequence.
            if (used_ > 0){
                move_down(current_index_);
            }
        }

        // Inserts the entry in the array. 
        data_[current_index_] = entry;

        // Increments the number of spots used in the array.
        used_++;
    }

    // Precondition: is_item returns true.
    // Postcondition: The current item has been removed from the sequence,
    //   and the item after this (if there is one) is now the new current item.
    void sequence::remove_current( )
    {
        // Makes sure there is a current item.
        assert(is_item());

        // Moves up the data in the array, overwrittig current item.
        move_up(current_index_);

        // Letting the sequence know when is the final of the sequence.
        // (the last item of the sequence is still there but we don't care)
        used_ = used_ - 1;
    }

    // Postcondition: The current object is equivalent to the object passed
    //   in.
    void sequence::operator =(const sequence& source){

        //Copying the attributtes of source.
        used_ = source.used_;
        current_index_ = source.current_index_;

        // Creating the array for the data.
        value_type* newData = new value_type[source.capacity_];

        // Copying the data from source to the array.
        for (size_t i = 0; i < source.used_; i++){
            newData[i] = source.data_[i];
        }

        // Deleting old data.
        delete [] data_;

        // Setting data to the new data.
        data_ = newData;

        // Copying the capacity of source.
        capacity_ = source.capacity_;
    }


    // CONSTANT MEMBER FUNCTIONS


    // Postcondition: The return value is the number of items in the sequence.
    sequence::size_type sequence::size( ) const
    {
        return used_;
    }

    // Postcondition: A true return value indicates that there is a valid
    //   "current" item that may be retrieved by activating the current
    //   member function (listed below). A false return value indicates that
    //   there is no valid current item.
    bool sequence::is_item( ) const
    {
        // Current index should never point to something that is not recorded
        // whithin the spots used. The following if makes sure that this
        // is correct. Otherwise, it returns false.
        if(current_index_ > used_ - 1){
            return false;
        }

        // If there is no spots used, it returns false.
        if(used_ == 0){
            return false;
        }

        // Otherwise, it returns true.
        return true;
    }

    //  Precondition: is_item( ) returns true.
    //  Postcondition: The item returned is the current item in the sequence.
    sequence::value_type sequence::current( ) const
    {
        return data_[current_index_];
    }

    //  Postcondition: The return value is true if both sequences contain no
    //    data items. Also, if the length is greater than zero, then the
    //    sequences must contain the same number of items and the items at the
    //    same location must be equal.
    bool sequence::operator ==(const sequence& other) const
    {   
        // If both sequences have zero spots used, there are equal.
        if(used_ == 0 && other.used_ == 0){
            return true;
        }

        // If both have at least one spot used, it makes sure
        // that their data are equal.
        if(size() > 0 && other.size() > 0){

            // Checking if their size are equal.
            if(size() != other.size()){
                return false;
            }

            // Making sure that their data inside are equal.
            for (size_t i = 0; i < size(); i++)
            {
                if (data_[i] != other.data_[i]){
                    return false;
                }
            }
            return true;
        }
        return false;
    }

    //  Postcondition: The return value is false if both sequences contain no
    //    data items. Also, if the length is greater than zero, then the
    //    sequences must not contain the same number of items or the items at
    //    the same location must not be equal.
    bool sequence::operator !=(const sequence& other) const
    {
        // Returns the oposite of boolean value of the function above.
        // (true if they are equal, false if they are not.)
        return !(sequence::operator ==(other));
    }


    // HELPER (PRIVATE) FUNCTIONS


    // Precondition: The capacity is (at least one) bigger than the number of
    //   items stored.
    // Postcondition: All data items from index to the number of items stored
    //   will be moved down one space (to open a space for another element).
    void sequence::move_down(size_type index)
    {
        // Making sure that the capacity it's at least one bigger than spots
        // used.
        assert(used_ < capacity_);

        // Moving the data down.
        for(size_t i = used_; i > index; i--)
        {
            data_[i] = data_[i-1];
        }  
    }


    // Precondition: There is at least one item stored.
    // Postcondition: All data items from index to the number of items stored
    //   will be moved up one space (to close up a space for a removed
    //   element).
    void sequence::move_up(size_type index)
    {
        // Making sure there is at least one item stored.
        assert(used_ > 0);
        
        // Moving the data up.
        for(size_t i = index; i < used_ - 1; i++)
        {
            data_[i] = data_[i+1];
        }
    }
}  
