#!/usr/bin/env python3
"""
update_datasets.py

Fetches and normalizes emojis, kaomoji, and nerd font symbols for Stowaway.
Sources:
- Emojis: emojibase compact dataset (Unicode emojis with tags and categories)
- Nerd Fonts: nerd-fonts glyphnames.json
- Kaomoji: curated collections merged with Stowaway's base expressions
"""

import json
import os
import sys
import urllib.request
from pathlib import Path

REPO_ROOT = Path(__file__).resolve().parent.parent
DATA_DIR = REPO_ROOT / "assets" / "data"

USER_AGENT = "Stowaway-Dataset-Updater/1.0 (https://github.com/AstraSuite/Stowaway)"


def fetch_json(url: str):
    """Fetch and decode JSON from a remote URL with custom User-Agent."""
    print(f"Fetching {url}...")
    req = urllib.request.Request(url, headers={"User-Agent": USER_AGENT})
    with urllib.request.urlopen(req) as resp:
        return json.loads(resp.read().decode("utf-8"))


def update_emojis():
    """Fetch emojis from emojibase and format into assets/data/emojis.json."""
    url = "https://raw.githubusercontent.com/milesj/emojibase/refs/heads/master/packages/data/en/compact.raw.json"
    data = fetch_json(url)

    # emojibase group mapping
    group_map = {
        0: "Smileys",
        1: "People",
        2: "People",
        3: "Animals",
        4: "Food",
        5: "Travel",
        6: "Activities",
        7: "Objects",
        8: "Symbols",
        9: "Flags",
    }

    emojis = []
    seen = set()

    for item in data:
        char = item.get("unicode")
        if not char or char in seen:
            continue
        seen.add(char)

        group_id = item.get("group")
        category = group_map.get(group_id, "Symbols")

        raw_label = item.get("label", "").strip()
        name = raw_label.title()

        tags = item.get("tags", [])
        tokens = []
        for word in (raw_label.lower().split() + [t.lower() for t in tags]):
            clean = "".join(ch for ch in word if ch.isalnum() or ch in "-_")
            if clean and clean not in tokens:
                tokens.append(clean)
        keywords = " ".join(tokens)

        emojis.append({
            "c": char,
            "name": name,
            "cat": category,
            "keys": keywords
        })

    output_path = DATA_DIR / "emojis.json"
    DATA_DIR.mkdir(parents=True, exist_ok=True)
    with open(output_path, "w", encoding="utf-8") as f:
        json.dump(emojis, f, indent=2, ensure_ascii=False)
        f.write("\n")

    print(f"Successfully updated emojis.json with {len(emojis)} emojis.")


def update_symbols():
    """Fetch Nerd Fonts glyphs, combine with standard unicode symbols, and write assets/data/symbols.json."""
    url = "https://raw.githubusercontent.com/ryanoasis/nerd-fonts/refs/heads/master/glyphnames.json"
    data = fetch_json(url)
    data.pop("METADATA", None)

    # Map Nerd Font prefixes to clean UI category names
    prefix_to_cat = {
        "cod": "Codicons",
        "custom": "Custom",
        "dev": "Devicons",
        "extra": "Extra",
        "fa": "Font Awesome",
        "fae": "Font Awesome Extension",
        "iec": "IEC Power",
        "indent": "Indentation",
        "indentation": "Indentation",
        "linux": "Logos",
        "md": "Material Design",
        "oct": "Octicons",
        "pl": "Powerline",
        "ple": "Powerline Extra",
        "pom": "Pomicons",
        "seti": "Seti-UI",
        "weather": "Weather",
    }

    # Retain existing standard non-Nerd-Font symbols (Arrows, Math, Greek, Currency, Typography)
    existing_symbols_path = DATA_DIR / "symbols.json"
    standard_categories = {"Arrows", "Math", "Greek", "Currency", "Typography"}
    retained_standard = []
    seen_chars = set()

    if existing_symbols_path.exists():
        try:
            with open(existing_symbols_path, "r", encoding="utf-8") as f:
                existing_data = json.load(f)
                for item in existing_data:
                    if item.get("cat") in standard_categories and item.get("c"):
                        retained_standard.append(item)
                        seen_chars.add(item["c"])
        except Exception as e:
            print(f"Warning: Could not read existing symbols.json: {e}")

    symbols = list(retained_standard)

    for key, val in data.items():
        char = val.get("char")
        if not char or char in seen_chars:
            continue
        seen_chars.add(char)

        prefix = key.split("-", 1)[0] if "-" in key else "other"
        cat = prefix_to_cat.get(prefix, "Nerd Fonts")

        raw_name = key.split("-", 1)[1] if "-" in key else key
        readable = raw_name.replace("_", " ").replace("-", " ")
        name = readable.title()
        code = val.get("code", "")

        keywords = f"{key} {readable} {code}".lower()

        symbols.append({
            "c": char,
            "name": name,
            "cat": cat,
            "keys": keywords
        })

    output_path = DATA_DIR / "symbols.json"
    DATA_DIR.mkdir(parents=True, exist_ok=True)
    with open(output_path, "w", encoding="utf-8") as f:
        json.dump(symbols, f, indent=2, ensure_ascii=False)
        f.write("\n")

    print(f"Successfully updated symbols.json with {len(symbols)} symbols ({len(retained_standard)} standard symbols, {len(symbols) - len(retained_standard)} nerd font glyphs).")


def update_kaomoji():
    """Fetch kaomoji and merge with existing curated kaomoji."""
    existing_path = DATA_DIR / "kaomoji.json"
    kaomoji_list = []
    seen_chars = set()

    # Load existing curated expressions first to retain their specific labels/tags
    if existing_path.exists():
        try:
            with open(existing_path, "r", encoding="utf-8") as f:
                existing_data = json.load(f)
                for item in existing_data:
                    c = item.get("c")
                    if c and c not in seen_chars:
                        kaomoji_list.append(item)
                        seen_chars.add(c)
        except Exception as e:
            print(f"Warning: Could not load existing kaomoji: {e}")

    # Fetch supplementary kaomoji from xav-ie/generate-kaomoji
    url = "https://raw.githubusercontent.com/xav-ie/generate-kaomoji/main/kaomoji.json"
    try:
        remote_data = fetch_json(url)
        items = remote_data.get("kaomoji", [])

        # Category normalization
        cat_map = {
            "joy": "Happy",
            "happiness": "Happy",
            "love": "Cute",
            "affection": "Cute",
            "cute": "Cute",
            "anger": "Angry",
            "sadness": "Sad",
            "indifference": "Shrug",
            "confusion": "Shrug",
            "doubt": "Shrug",
            "fear": "Sad",
            "pain": "Sad",
        }

        for entry in items:
            char = entry.get("value", "").strip()
            if not char or char in seen_chars:
                continue
            seen_chars.add(char)

            raw_cat = entry.get("category", "Happy").lower()
            cat = cat_map.get(raw_cat, raw_cat.title())
            name = f"{cat} Kaomoji"
            keys = f"{cat.lower()} {raw_cat} kaomoji emotion expression"

            kaomoji_list.append({
                "c": char,
                "name": name,
                "cat": cat,
                "keys": keys
            })
    except Exception as e:
        print(f"Warning: Could not fetch remote kaomoji: {e}")

    output_path = DATA_DIR / "kaomoji.json"
    DATA_DIR.mkdir(parents=True, exist_ok=True)
    with open(output_path, "w", encoding="utf-8") as f:
        json.dump(kaomoji_list, f, indent=2, ensure_ascii=False)
        f.write("\n")

    print(f"Successfully updated kaomoji.json with {len(kaomoji_list)} kaomoji expressions.")


def main():
    print("Starting dataset updates...")
    update_emojis()
    update_symbols()
    update_kaomoji()
    print("Dataset updates completed successfully.")


if __name__ == "__main__":
    main()
