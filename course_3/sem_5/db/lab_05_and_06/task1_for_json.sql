SELECT TOP 3 *
from MobileGames.Developers as D
join MobileGames.Games AS Games
     on Games.developer_id = D.id
FOR JSON AUTO