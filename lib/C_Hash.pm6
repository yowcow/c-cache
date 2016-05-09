use v6;
use NativeCall;

unit module C_Hash;

sub library { 'resources/libhash.so' }

class C_Hash::Pair is repr('CStruct') {
    has Pointer[Str] $.key;
    has Pointer[Str] $.val;
}

class C_Hash::Node is repr('CStruct') {
    has C_Hash::Pair $.pair;
    has C_Hash::Node $.next;
    has C_Hash::Node $.prev;

    method key(::?CLASS:D: --> Str) { $!pair.key.deref }
    method val(::?CLASS:D: --> Str) { $!pair.val.deref }
}

class C_Hash::Bucket is repr('CStruct') {
    has uint32 $.size;
    has C_Hash::Node $.head;
    has C_Hash::Node $.tail;
}

class C_Hash::Hash is repr('CStruct') {
    has uint32 $.seed;
    has CArray[C_Hash::Bucket] $.buckets;

    sub create(--> ::?CLASS)
        is native(&library)
        is symbol('Hash_create') { * }

    sub destroy(::?CLASS)
        is native(&library)
        is symbol('Hash_destroy') { * }

    sub set(::?CLASS, Str, Str --> C_Hash::Node)
        is native(&library)
        is symbol('Hash_set') { * }

    sub get(::?CLASS, Str --> C_Hash::Node)
        is native(&library)
        is symbol('Hash_get') { * }

    sub delete(::?CLASS, Str --> bool)
        is native(&library)
        is symbol('Hash_delete') { * }

    method new(::?CLASS:U:) { create() }

    method set(::?CLASS:D: Str:D $key, Str:D $val --> C_Hash::Node) {
        set(self, $key, $val);
    }

    method get(::?CLASS:D: Str:D $key --> C_Hash::Node) {
        get(self, $key);
    }

    method delete(::?CLASS:D: Str:D $key --> bool) {
        delete(self, $key);
    }

    method free(::?CLASS:D:) {
        destroy(self);
    }

    method DESTROY(::?CLASS:D:) {
        self.free;
    }
}
