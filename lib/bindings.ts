const addon = require('../build/Release/eot2ttf');

export function eot2ttf(eotBuffer: Buffer): Buffer {
    return addon.EOT2ttfBuffer(eotBuffer, {});
}