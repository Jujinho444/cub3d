# Résultats attendus

Chaque erreur doit afficher `Error`, puis le message, sur la sortie d'erreur.
Les fichiers valides ne doivent rien afficher et sortir avec le code 0.

pour compiler toutes les erreurs en même temps :

``for f in maps/*/*.cub maps/invalid/*/*.cub; do echo "== $f"; valgrind -q --leak-check=full --show-leak-kinds=all ./cub3D "$f"; echo "exit: $?"; done``

lancer ``bash run_tests.sh`` dans le dossier racine du projet.

## valid/ : aucune sortie, code 0

| Fichier | Ce qui est testé |
|---|---|
| v01_basic | cas nominal |
| v02_shuffled_order | identifiants dans le désordre |
| v03_multiple_spaces | espaces multiples, en début et en fin de ligne |
| v04_black_and_leading_zeros | `F 0,0,0`, zéros en tête (`000`, `010`) |
| v05_spaces_in_colors | espaces autour des virgules |
| v06_irregular_map | map irrégulière, espaces de tête = vide extérieur |
| v07_trailing_empty_lines | lignes vides (et d'espaces) après la map |
| v08_no_final_newline | pas de `\n` à la fin du fichier |
| v09_empty_lines_in_header | lignes vides avant et entre les éléments |
| v10_space_in_texture_path | espace au milieu d'un chemin |
| v11_player_south | joueur `S` |
| v12_inner_walls_player_east | murs intérieurs, joueur `E` |
| v13_tiny_player_west | map minimale, joueur `W` |

## invalid/header/

| Fichier | Message attendu |
|---|---|
| h01_unknown_identifier | Unknown identifier |
| h02_no_space_after_id | Unknown identifier |
| h03_lowercase_id | Unknown identifier |
| h04_duplicate_texture | Identifier is duplicated |
| h05_duplicate_color | Identifier is duplicated |
| h06_missing_element_then_map | Unknown identifier (voir remarque 1) |
| h07_missing_element_eof | missing element in header |
| h08_empty_value | empty value |
| h09_id_alone | Unknown identifier |
| h10_color_256 | Color Value out of range |
| h11_color_negative | Missing Color Value |
| h12_color_two_components | Incorrect Color format |
| h13_color_four_components | Incorrect Color format |
| h14_color_trailing_comma | Incorrect Color format |
| h15_color_empty_component | Missing Color Value |
| h16_color_non_digit | Incorrect Color format |
| h17_color_overflow | Color Value out of range |
| h18_color_space_in_number | Incorrect Color format |
| h19_color_plus_sign | Missing Color Value |
| h20_tab_separator | Unknown identifier |
| h21_missing_map | missing map |
| h22_missing_map_trailing_lines | missing map |
| h23_empty_file | missing element in header |
| h24_only_newlines | missing element in header |
| h25_two_paths | AUCUNE ERREUR actuellement (voir remarque 2) |
| h26_crlf_whole_file | Incorrect Color format (voir remarque 3) |
| h27_map_first | Unknown identifier |

## invalid/map/

| Fichier | Message attendu |
|---|---|
| m01_empty_line_inside | Incorrect Map, empty line inside map |
| m02_spaces_only_line_inside | Incorrect Map, empty line inside map |
| m03_open_top | Unclosed map |
| m04_open_left | Unclosed map |
| m05_interior_space | Unclosed map |
| m06_longer_line_below | Unclosed map |
| m07_player_on_edge | Unclosed map |
| m08_diagonal_gap | Unclosed map (choix des 8 voisins) |
| m09_no_player | One player in map is required |
| m10_two_players | One player in map is required |
| m11_invalid_char | Invalid character in map |
| m12_crlf_map_only | Invalid character in map (le `\r`) |
| m13_tab_in_map | Invalid character in map |
| m14_element_after_map | Incorrect Map, empty line inside map |
| m15_open_bottom_corner | Unclosed map |

## invalid/file/

| Commande | Message attendu |
|---|---|
| `./cub3D` | Wrong number of arguments in program |
| `./cub3D a.cub b.cub` | Wrong number of arguments in program |
| `./cub3D maps/invalid/file/f01_wrong_extension.txt` | Wrong filename extension |
| `./cub3D maps/invalid/file/f02_double_extension.cub.txt` | Wrong filename extension |
| `./cub3D maps/invalid/file/.cub` | Wrong filename extension |
| `./cub3D maps/invalid/file/f03_directory.cub` | `<chemin>: Is a directory` |
| `./cub3D maps/invalid/file/f04_no_read_permission.cub` (après `chmod 000`) | `<chemin>: Permission denied` |
| `./cub3D maps/nexiste_pas.cub` | `<chemin>: No such file or directory` |

## Remarques

1. Un fichier entièrement en fins de ligne Windows échoue sur la première couleur,
   parce que `ft_strtrim(" \n")` laisse le `\r`. Les chemins de texture gardent
   aussi un `\r` final.
