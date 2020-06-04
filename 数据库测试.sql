

--if exists (select * from sys.databases where name = ’数据库名’)  
 -- drop database [数据库名]  if exists (select * from sys.databases where name = ’数据库名’)
 -- drop database [数据库名]



--建表
USE [test]
GO

/****** Object:  Table [dbo].[TestTable]    Script Date: 06/03/2020 14:44:15 ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

if not exists (select * from sysobjects where id = object_id(N'[dbo].[TestTable]') and OBJECTPROPERTY(ID, N'IsUserTable') = 1)  --判断表是否存在
CREATE TABLE [dbo].[TestTable](
	[id] [int] NOT NULL,
	[gold] [bigint] NOT NULL,
	[age] [int] NOT NULL,
	[bChild] [tinyint] NOT NULL,
	[name] [nvarchar](50) NOT NULL,
	[interest] [nvarchar](50) NOT NULL
) ON [PRIMARY]

GO



----------------------------------------------------------------------------------------------------
--建存储过程
USE [test]
GO

IF EXISTS (SELECT * FROM DBO.SYSOBJECTS WHERE ID = OBJECT_ID(N'[dbo].[GSP_GS_SaveTestData]') and OBJECTPROPERTY(ID, N'IsProcedure') = 1)--判断储过程是否存在
DROP PROCEDURE [dbo].GSP_GS_SaveTestData
GO

IF EXISTS (SELECT * FROM DBO.SYSOBJECTS WHERE ID = OBJECT_ID(N'[dbo].[GSP_GS_SelectTestData]') and OBJECTPROPERTY(ID, N'IsProcedure') = 1)
DROP PROCEDURE [dbo].GSP_GS_SelectTestData
GO


SET QUOTED_IDENTIFIER ON 
GO

SET ANSI_NULLS ON 
GO


----------------------------------------------------------------------------------------------------

-- 保存数据
CREATE  PROCEDURE dbo.GSP_GS_SaveTestData
	@Id				int,
	@gold			bigint,
	@age			int,	
	@bChild			tinyint,
	@name			nvarchar(50),
	@interest		nvarchar(50)
WITH ENCRYPTION AS

-- 设置属性
SET NOCOUNT ON

-- 执行逻辑
BEGIN

	INSERT INTO TestTable (id, gold, age,bChild,name,interest)
	VALUES (@Id,@gold, @age,@bChild, @name,@interest)
END

RETURN 0

GO

----------------------------------------------------------------------------------------------------

-- 取出数据
CREATE  PROCEDURE dbo.GSP_GS_SelectTestData

WITH ENCRYPTION AS

-- 设置属性
SET NOCOUNT ON

-- 执行逻辑
BEGIN

	SELECT *
	FROM TestTable(NOLOCK)
	
END

RETURN 0

GO
----------------------------------------------------------------------------------------------------

