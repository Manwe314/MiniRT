#!/bin/bash

# Parcourir tous les fichiers .c dans le répertoire actuel
for file in *.c; do
    # Vérifier si le fichier existe
    if [[ -f "$file" ]]; then
        # Créer un fichier tampon pour stocker le résultat de la commande
        temp_file="$file.temp"

        # Appliquer c_formatter_42 sur le fichier et stocker le résultat dans le fichier tampon
        c_formatter_42 < "$file" > "$temp_file"

        # Vérifier si la commande s'est exécutée avec succès
        if [[ $? -eq 0 ]]; then
            # Copier le contenu du fichier tampon dans le fichier d'origine
            cp "$temp_file" "$file"
            echo "Le fichier $file a été mis à jour avec succès."
        else
            echo "Une erreur s'est produite lors de l'exécution de c_formatter_42 sur le fichier $file."
        fi

        # Supprimer le fichier tampon
        rm "$temp_file"
    fi
done
