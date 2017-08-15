#ifndef NDARRAY_H
#define NDARRAY_H

#include <shape.h>

template <typename T> class NDArray 
{ 
    private:
        T    *_buffer;                          // pointer on flattened data array in memory
        int  *_shapeInfo;                       // contains shape info:  matrix rank, numbers of elements per each dimension, dimensions strides, c-like or fortan-like order, element-wise-stride
        bool  _allocated;                       // indicates whether user allocates memory for array by himself, in opposite case the memory must be allocated from outside 

        static constexpr T EPSN = (T) 1e-5f;    // take into account the tolerance in arrays element-wise comparison    
        
    public:    
        // default constructor, do not allocate memory, memory for array is passed from outside 
        NDArray(T *buffer = nullptr, int *shapeInfo = nullptr);

        // copy constructor
        NDArray(const NDArray<T>& arr);
    
        // this constructor creates 2D NDArray, memory for array is allocated in constructor 
        explicit NDArray(const int rows, const int columns, const char order);
        
        // this constructor creates NDArray as single row (dimension is 1xlength), memory for array is allocated in constructor 
        explicit NDArray(const int length, const char order);
        
        // creates new NDArray using shape information from "shape" array, set all elements in new array to be zeros
        explicit NDArray(const int* shape);

        // this constructor creates new array using shape information contained in initializer_list argument
        explicit NDArray(const char order, const std::initializer_list<int>& shape);

        // This method replaces existing buffer/shapeinfo, AND releases original pointers (if releaseExisting TRUE)
        void replacePointers(T* buffer, int* shapeInfo, bool releaseExisting = true);
        
        // assignment operator
        NDArray<T>& operator=(const NDArray<T>& other);

        // equality operator
        bool operator==(const NDArray<T>& other) const;
        
        // set _buffer
        void setBuff(const T* buff) 
        { _buffer = buff; }
        
        // get _buffer
        T* getBuff() const
        { return _buffer; }
    
        // set _shapeInfo
        void setShape(const int* shape) 
        { _shapeInfo = shape; }

        // get _shapeInfo
        int* getShape() const
        { return _shapeInfo; }
        
        // This method returns order of this NDArray
        char ordering() const {
            return shape::order(_shapeInfo);
        }

        // This method returns shape portion of shapeInfo
        int *shapeOf() const {
            return shape::shapeOf(_shapeInfo);
        }

        // This method returns strides portion of shapeInfo
        int *stridesOf() const {
            return shape::stride(_shapeInfo);
        }

        // This method returns rank of this NDArray
        int rankOf() const {
            return shape::rank(_shapeInfo);
        }

        // This method returns length of this NDArray
        Nd4jIndex lengthOf() const {
            return shape::length(_shapeInfo);
        }

        // This method returns number of rows in this NDArray
        int rows() const {
            return shapeOf()[0];
        }

        // This method returns number of columns in this NDArray
        int columns() const {
            return shapeOf()[1];
        }

        // This method returns sizeof(T) for this NDArray
        int sizeOfT() const {
            return sizeof(T);
        }

        // check two arrays whether they have the same shapes, arrays are considered to have the same shapes if they have the same ranks and corresponding dimensions
        bool isSameShape(const NDArray<T>& other) const;            
        
        // print information about array shape
        void printShapeInfo() const {
            //shape::printShapeInfo(_shapeInfo);
            shape::printShapeInfoLinear(_shapeInfo);
        }

        // This method assigns values of given NDArray to this one, wrt order
        void assign(const NDArray<T> *other);

        // This method assigns given value to all elements in this NDArray
        void assign(const T value);

        // This method returns new copy of this NDArray, optionally in different order
        NDArray<T>* dup(const char newOrder);


        // This method returns sum of all elements of this NDArray
        T sumNumber() const;

        // This method returns mean number of this NDArray
        T meanNumber() const;

        // method calculates sum along dimension(s) in this array and save it to row: as new NDArray with dimensions 1xN
        NDArray<T>* sum(const std::initializer_list<int>& dimensions) const;

        // eventually this method reduces this array to 1xN row 
        template<typename OpName> NDArray<T>* reduceAlongDimension(const std::initializer_list<int>& dimensions) const;

        //
        template<typename OpName> T reduceNumber() const;

        // 
        template<typename OpName> T reduceNumber(T* extraParams) const;
        
        // perform array transformation
        template<typename OpName> void applyTransform();
        
        // perform array transformation
        template<typename OpName> void applyTransform(T *extraParams);

        // method makes copy of this array and applies to the copy the transpose operation, that is this array remains unaffected 
        NDArray<T> *transpose() const;

        // This method applies in-place transpose to this array, so this array becomes transposed 
        void transposei();
        
        // This method returns true if buffer && shapeInfo were defined
        bool nonNull() const {
            return this->_buffer != nullptr && this->_shapeInfo != nullptr;
        }
  
        // This method returns true if two arrays are equal, with custom or default Eps value of 1e-5, false otherwise
        bool equalsTo(const NDArray<T>& other, T eps = EPSN) const;
   
        // Return value from linear buffer
        T getScalar(const Nd4jIndex i) const;

        // Returns value from 2D matrix by coordinates/indexes 
        T getScalar(const int i, const int j) const;

        // returns value from 3D tensor by coordinates
        T getScalar(const int i, const int k, const int j) const;

        // This method sets value in linear buffer to position i
        void putScalar(const Nd4jIndex i, const T value);

        // This method sets value in 2D matrix to position i, j 
        void putScalar(const int i, const int j, const T value);

        // This method sets value in 3D matrix to position i,j,k
        void putScalar(const int i, const int k, const int j, const T value);

        // This method adds given row to all rows in this NDArray, that is this array becomes affected
        void addiRowVector(const NDArray<T> *row);


    // default destructor
    ~NDArray();

};




#endif

