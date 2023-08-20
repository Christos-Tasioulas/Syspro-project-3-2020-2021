#include "CyclicBuffer.h"
#include <iostream>
#include <unistd.h>

CyclicBuffer::CyclicBuffer(int cbs)
{
    this->array = new string[cbs];
    this->size = cbs;
    this->count = 0;
    this->start = 0;
    this->end = -1;

    pthread_mutex_init(&this->mtx, 0);
	pthread_cond_init(&this->cond_nonempty, 0);
	pthread_cond_init(&this->cond_nonfull, 0);
}

CyclicBuffer::~CyclicBuffer()
{
    pthread_cond_destroy(&this->cond_nonempty);
	pthread_cond_destroy(&this->cond_nonfull);
	pthread_mutex_destroy(&this->mtx);

    delete[] this->array;
}

string* CyclicBuffer::get_array(void) const
{
    return this->array;
}

string CyclicBuffer::get_string()
{
    // only one thread at a time can execute this function
    pthread_mutex_lock(&(this->mtx));
    // waiting for the buffer to fill up
	while (this->count <= 0) {
		pthread_cond_wait(&(this->cond_nonempty), &(this->mtx));
		}
	string s = this->array[this->start];
    // increasing the start by one or turning it back to 0 if we reached the cyclicBufferSize
	this->start = (this->start + 1) % this->size;
	this->count--;
	pthread_mutex_unlock(&this->mtx);
    return s;
}

void CyclicBuffer::set_string(string s)
{
    // only one thread at a time can execute this function
    pthread_mutex_lock(&this->mtx);
    // waiting for the buffer not to be full
	while (this->count >= this->size) {
		pthread_cond_wait(&this->cond_nonfull, &this->mtx);
		}
    // increasing the end by one or turning it back to 0 if we reached the cyclicBufferSize
	this->end = (this->end + 1) % this->size;
	this->array[this->end] = s;
	this->count++;
	pthread_mutex_unlock(&this->mtx);
}

int CyclicBuffer::get_size(void) const
{
    return this->size;
}

int CyclicBuffer::get_count(void) const
{
    return this->count;
}

int CyclicBuffer::get_start(void) const
{
    return this->start;
}

int CyclicBuffer::get_end(void) const
{
    return this->end;
}

pthread_cond_t CyclicBuffer::get_nonempty(void) const
{
    return this->cond_nonempty;
}

pthread_cond_t CyclicBuffer::get_nonfull(void) const
{
    return this->cond_nonfull;
}    