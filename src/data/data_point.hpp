#ifndef DATA_DATA_POINT_HPP_
#define DATA_DATA_POINT_HPP_

#include <cstdint>

namespace hyped {
    namespace data {
        template <typename T>
        class DataPoint {
            public:
                DataPoint(){}
                DataPoint(uint32_t, const T& value) : timestamp(timestamp), value(value){}
                uint32_t timestamp;
                T value;

        };
    }
}

#endif