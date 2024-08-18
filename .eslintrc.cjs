module.exports = {
    'env': {
        'es2015': true,
        'es2021': true,
        'node': true,
    },
    'extends': [
        'eslint:recommended', 
        'plugin:@typescript-eslint/eslint-recommended', 
        'plugin:@typescript-eslint/recommended'
    ],
    'parser': '@typescript-eslint/parser',
    'plugins': [
        '@typescript-eslint'
    ],
    'overrides': [
    ],
    'rules': {
        "object-curly-spacing": ["error", "always"],
        "indent": ["error", 4],
        "linebreak-style": ["error", "unix"],
        "quotes": ["error", "single"],
        "semi": ["error", "always"],

        // override configuration set by extending "eslint:recommended"
        "no-empty": "warn",
        "no-cond-assign": ["error", "always"],

        // disable rules from base configurations
        "for-direction": "off",
        
        "@typescript-eslint/ban-ts-comment": "off",
    },
    root: true,
};