//
// Created by pc on 2023/1/16.
//

#ifndef TEST_NONCOPYABLE_H
#define TEST_NONCOPYABLE_H
class noncopyable{
public:
        noncopyable(const noncopyable &)=delete;
	const noncopyable& operator=(const noncopyable &) =delete;

protected:
    noncopyable()=default;
    ~noncopyable()=default;
};
#endif //TEST_NONCOPYABLE_H
