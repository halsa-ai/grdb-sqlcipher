#ifndef grdb_config_h
#define grdb_config_h

#include <SQLCipher/sqlite3.h>

/// SQLCipher's sqlite3.h declares its key functions only when SQLITE_HAS_CODEC is
/// defined, and defining it for Swift's importer needs an unsafe compiler flag, which
/// SwiftPM forbids in dependencies requested by version number. The functions are in
/// the SQLCipher binary regardless, so they are declared here, with the signatures from
/// SQLCipher's own header, instead.
#ifndef SQLITE_HAS_CODEC
extern int sqlite3_key(sqlite3 *db, const void *pKey, int nKey);
extern int sqlite3_rekey(sqlite3 *db, const void *pKey, int nKey);
#endif

typedef void(*_errorLogCallback)(void *pArg, int iErrCode, const char *zMsg);

/// Wrapper around sqlite3_config(SQLITE_CONFIG_LOG, ...) which is a variadic
/// function that can't be used from Swift.
static inline void _registerErrorLogCallback(_errorLogCallback callback) {
    sqlite3_config(SQLITE_CONFIG_LOG, callback, 0);
}

#if SQLITE_VERSION_NUMBER >= 3029000
/// Wrapper around sqlite3_db_config() which is a variadic function that can't
/// be used from Swift.
static inline void _disableDoubleQuotedStringLiterals(sqlite3 *db) {
    sqlite3_db_config(db, SQLITE_DBCONFIG_DQS_DDL, 0, (void *)0);
    sqlite3_db_config(db, SQLITE_DBCONFIG_DQS_DML, 0, (void *)0);
}

/// Wrapper around sqlite3_db_config() which is a variadic function that can't
/// be used from Swift.
static inline void _enableDoubleQuotedStringLiterals(sqlite3 *db) {
    sqlite3_db_config(db, SQLITE_DBCONFIG_DQS_DDL, 1, (void *)0);
    sqlite3_db_config(db, SQLITE_DBCONFIG_DQS_DML, 1, (void *)0);
}
#else
static inline void _disableDoubleQuotedStringLiterals(sqlite3 *db) { }
static inline void _enableDoubleQuotedStringLiterals(sqlite3 *db) { }
#endif
#endif /* grdb_config_h */
