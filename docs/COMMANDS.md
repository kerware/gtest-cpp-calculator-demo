# Commandes GoogleTest utiles

Lister les tests :

```bash
./build/calculator_tests --gtest_list_tests
```

Filtrer une suite :

```bash
./build/calculator_tests --gtest_filter='BeginnerAssertions.*'
```

Exclure des tests :

```bash
./build/calculator_tests --gtest_filter='-*DeathTests*'
```

Lancer uniquement les death tests en mode threadsafe :

```bash
./build/calculator_tests --gtest_filter='*DeathTests*' --gtest_death_test_style=threadsafe
```

Répéter et mélanger :

```bash
./build/calculator_tests --gtest_repeat=10 --gtest_shuffle --gtest_random_seed=42
```

Produire un rapport XML :

```bash
./build/calculator_tests --gtest_output=xml:build/gtest-report.xml
```

Mode fail-fast :

```bash
./build/calculator_tests --gtest_fail_fast
```

Arrêt sur échec pour débogueur :

```bash
./build/calculator_tests --gtest_break_on_failure
```

Shard 1 sur 4 :

```bash
GTEST_TOTAL_SHARDS=4 GTEST_SHARD_INDEX=0 ./build/calculator_tests
```
