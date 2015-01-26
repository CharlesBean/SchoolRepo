#pragma once

#ifndef HASH_FUNC_H
#define HASH_FUNC_H

#include <string>

/**
 * These are the signatures for the hash functions.
 * You must implement them in the source file.
 * The choice of functions is up to you.
 */
unsigned int HashA(const std::string& s);
unsigned int HashB(const std::string& s);
unsigned int HashC(const std::string& s);

#endif