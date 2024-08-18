import assert from 'assert';
import { eot2ttf } from '../dist/bindings.js';
import fs from 'fs';

function testDecoderOS2() {
    var src = new Uint8Array(fs.readFileSync('./tests/fixtures/test_v0.eot'))
    var dst = new Uint8Array(fs.readFileSync('./tests/fixtures/test_v0.ttf'))

    assert.deepEqual(eot2ttf(src), dst)
}
function testDecoder() {
    var src = new Uint8Array(fs.readFileSync('./tests/fixtures/test.eot'))
    var dst = new Uint8Array(fs.readFileSync('./tests/fixtures/test.ttf'))

    assert.deepEqual(eot2ttf(src), dst)
}

assert.doesNotThrow(testDecoderOS2, undefined, "testDecoderOS2 threw an exception");
assert.doesNotThrow(testDecoder, undefined, "testDecoder threw an exception");

console.log("Tests passed- everything looks OK!");