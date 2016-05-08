use v6;
use C_Hash;
use Test;

subtest {

    my C_Hash::Hash $hash .= new;

    $hash.set("hoge", "fuga");

    subtest {
        my C_Hash::Node $node = $hash.get("hoge");

        ok $node.defined;
        is $node.val, 'fuga';
    }, '"hoge" exists';

    subtest {
        ok not $hash.get("HOGE").defined;
    }, '"HOGE" doesnt exist';

    $hash.delete("hoge");

    subtest {
        ok not $hash.get("hoge").defined;
    }, '"hoge" doesnt exist';

    $hash.free;

}, 'Test CHash::Hash';

done-testing;
