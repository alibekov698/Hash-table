
#include "set.h"

// From previous task:

bool equal( const std::string& s1, const std::string& s2 )
{
    if(s1.size() != s2.size())
    {
        return false;
    } else {
        for( size_t i = 0; i < s1.size(); i++ )
        {
            if(tolower(s1[i]) != tolower(s2[i]))
                return false;
        }
        return true;
    }
}

size_t hash( const std::string& st )
{
    size_t val = 0;
    size_t n = st.size();

    for (size_t i = 0; i < st.size(); i++)
    {
        n --;
        val = int(tolower(st[i])) + val;
    }
    return val;
}

bool set::contains( const std::string& s ) const
{
    size_t index = hash(s) % buckets.size();

    for( auto it = buckets[index].begin(); it != buckets[index].end(); it++ )
    {
        if ( equal(*it, s) )
            return true;
    }
    return false;
}

bool set::simp_insert( const std::string& s )
{
    size_t index = hash(s) % buckets.size();

    if ( !contains(s) )
    {
        set_size ++;
        buckets[index].push_back(s);
        return true;
    } else {
        return false;
    }
}

bool set::insert( const std::string& s )
{
    if( !simp_insert(s))
    {
        return false;
    } else if (set_size > max_load_factor * buckets.size()) {
        size_t new_size = buckets.size() * 2;

        while (set_size > (max_load_factor * new_size))
        {
            new_size *= 2;
        }
        rehash(new_size);
    }
    return true;
}

void set::rehash( size_t newbucketsize )
{
    if( newbucketsize < 4 )
    {
        newbucketsize = 4;
    }
    std::vector< std::list< std::string >> newbuckets = std::vector< std::list< std::string >> ( newbucketsize );

    for (size_t j = 0; j < buckets.size(); j++)
    {
        for ( auto it = buckets[j].begin(); it != buckets[j].end(); it++ )
        {
            size_t new_index = hash(*it) % newbuckets.size();
            newbuckets[new_index].push_back(*it);
        }
    }
    buckets = newbuckets;
}

bool set::remove( const std::string& s )
{
    size_t index = hash(s) % buckets.size();

    for( auto it = buckets[index].begin(); it != buckets[index].end(); it++ )
    {
        if ( equal(*it, s) )
        {
            buckets[index].erase(it);
            set_size --;
            return true;
        }
    }
    return false;
}

void set::clear( )
{
    buckets.clear();
    set_size = 0;
}

std::ostream& set::print( std::ostream& out ) const
{
    for (size_t j = 0; j < buckets.size(); j++)
    {
        out << "bucket[" << j << "]:    { ";
        int size_of_single_bucket = buckets[j].size();

        for ( auto it = buckets[j].begin(); it != buckets[j].end(); it++ )
        {
            size_of_single_bucket--;
            out << *it;
            if(size_of_single_bucket != 0)
                out << ", ";
        }
        out << " }\n";
    }
    return out;
}

std::ostream& set::printstatistics( std::ostream& out ) const
{
   std::cout << "set size =            " << size( ) << "\n";
   std::cout << "load factor =         " << loadfactor( ) << " ( max = " << max_load_factor << " )\n";
   std::cout << "standard deviation =  " << standarddev( ) << "\n";
   return out;
}


