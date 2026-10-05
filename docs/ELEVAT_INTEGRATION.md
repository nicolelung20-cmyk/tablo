# Elevat / Hermes integration

Tablo is the physical e-ink display worker for nicolelung20-cmyk/elevated-associates.

- Hermes remains the conversational/agent interface.
- Elevat Associates remains the canonical control plane.
- Tablo is read-only presentation.
- Tablo never holds trading keys, OAuth refresh tokens, or money-movement credentials.

Data flow:
Hermes -> Elevat control plane -> /api/tablo/v1/status -> Tablo HTTP connector -> e-ink widgets

Configure an HTTP connector with id `elevat`, kind `http`, URL `<private control-plane base>/api/tablo/v1/status`, interval `120`, and an empty map. Tablo's HTTP parser accepts the slot-object response format directly.

Recommended dashboard roles: Dashboard 1 = ELEVAT/HERMES/REVENUE/SYSTEM; Dashboard 2 = PAPER TRADING/MARKETS; Dashboard 3 = existing personal/environment widgets.

Live trading authority stays outside Tablo.
